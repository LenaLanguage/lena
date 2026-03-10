module Lena

export I8,I16,I32,I64, U8,U16,U32,U64, F32,F64, LBool, @lena

# --- типы (алиасы, чтобы в Julia-подписях писать Lena.I64 и т.д.) ---
const I8  = Int8
const I16 = Int16
const I32 = Int32
const I64 = Int64

const U8  = UInt8
const U16 = UInt16
const U32 = UInt32
const U64 = UInt64

const F32 = Float32
const F64 = Float64

# булевый тип в Lena у тебя 1 байт, представим через UInt8 на уровне C ABI
const LBool = UInt8

# --- таблица маппинга: Lua/Julia type expr -> Julia concrete type to use in Base.@ccallable ---
# входом для макроса будут выражения типа :(Lena.I64) или :(Lena.I64) в AST.
function _map_lena_type_expr(expr)
    # expr может быть :(:., :Lena, :I64) или просто :I64 (если импортировали)
    # универсальная обработка:
    if expr isa Symbol
        # если просто I64
        nm = String(expr)
    elseif expr isa Expr && expr.head == :. && length(expr.args) == 2
        # Expr(:., :Lena, :I64)
        nm = String(expr.args[2])
    else
        error("Unsupported type expression in @lena: $expr")
    end

    # вернуть символ типа Julia (он же будет использован в @ccallable)
    if nm == "I8"   return :Int8
    elseif nm == "I16" return :Int16
    elseif nm == "I32" return :Int32
    elseif nm == "I64" return :Int64
    elseif nm == "U8"  return :UInt8
    elseif nm == "U16" return :UInt16
    elseif nm == "U32" return :UInt32
    elseif nm == "U64" return :UInt64
    elseif nm == "F32" return :Float32
    elseif nm == "F64" return :Float64
    elseif nm == "LBool" return :UInt8
    else
        error("Unknown Lena type name: $nm. Extend _map_lena_type_expr to support it.")
    end
end

# --- макрос @lena ---
# Использование:
# @lena function func1(x::Lena.I64, y::Lena.I64)::Lena.I64
#     ...
# end
#
# Макрос:
macro lena(fndef)
    # Проверяем, что передали function-определение
    if !(fndef isa Expr && fndef.head == :function)
        error("@lena must be applied to a function definition")
    end

    # Синтаксический разббор имени и аргументов:
    # fndef.args[1] — это либо Symbol (для короткой формы) либо Expr(:call, name, args...)
    sig = fndef.args[1]
    body = fndef.args[2]

    if sig isa Symbol
        fname = sig
        args_expr = Expr(:tuple)  # пустой
    elseif sig isa Expr && sig.head == :call
        fname = sig.args[1]
        args_expr = Expr(:tuple, sig.args[2:end]...)
    else
        error("Unsupported function signature in @lena: $sig")
    end

    # Попытка извлечь аннотированный возвращаемый тип, если есть:
    # fndef мог быть вида :(function (name(args...)) :: Ret ... end) — тогда sig находится в другом месте.
    rettype_expr = nothing
    # В Julia AST возвратный тип у функции представлен как :($(sig) :: RET) — если пользователь указал ::RET
    # Если function-expression имеет третий аргумент (body) и сигнатура с :: возможно быть внутри fndef.args[1] или fndef.head?
    # Попробуем найти :: в fndef (на простых формах это присутствует как Expr(:call, :::, ...)?)
    # Упростим: ожидаем, что возвращаемый тип, если указан, находится в fndef.args[1] как Expr(:call, name, args...)::Ret
    # Практический обход: если тело fndef has ::: at top of sig, парсим:
    if sig isa Expr && sig.head == :(::)
        # unlikely; but keep for safety
    end

    # Более практичный путь: попытка найти последний элемент fndef.args[2] если это Expr(:block)
    # Если пользователь указал возвращаемый тип -> он будет внутри fndef as Expr(:function, Expr(:call ... ), body)
    # We'll search the AST for an Expr(:::) in the function signature token:
    # but to keep macro robust we will require explicit return type annotation in the function header:
    #    function name(... )::Lena.I64
    # Otherwise fail with helpful message.
    # Try find return type:
    m = match(r"::", sprint(show, sig))
    # crude: check the string form
    if occursin("::", sprint(show, sig))
        # Re-parse: if signature expression is of form Expr(:call, Expr(::, name, rettype), args...) — complex
        # Simpler: transform whole fndef to string and attempt to parse rettype with regex — ugly...
        # Instead we try to locate a top-level Expr(:stype) in fndef (this is brittle).
    end

    # Simpler approach: accept only the common explicit syntax:
    # `function name(args...) :: SomeType ... end`
    # which in AST stores return type as fndef.args[1] maybe as Expr(:call, name, args...) but `fndef` may have extra.
    # To avoid fragile AST parsing, require the *user to include explicit return type annotation* and use the short form:
    #    @lena function func1(x::Lena.I64, y::Lena.I64)::Lena.I64
    # The macro will then look up the return type by examining `:(... )` of the function definition via
    # parsing the raw expression string. (workaround)
    #
    # Implementation detail: we'll reconstruct arguments and read their type annotations and the return annotation
    sig_expr = fndef.args[1]
    # handle signature like :(func1(x::Lena.I64, y::Lena.I64)::Lena.I64)
    # If last part of signature is Expr(::) pattern:
    ret_ann = nothing
    if sig_expr isa Expr && sig_expr.head == :call
        # check if sig itself contains :: as last element (some AST forms)
        # fallback: check fndef of the form: Expr(:function, Expr(:call, :func1, ...), body)
        # weirdness: return type annotation is actually attached to fndef as Expr(:function) where the first argument may be Expr(:call, :(::), ...)
        # To avoid spending too much time on all edge cases, implement simpler: require that return type is present as fndef.args[1].args[end] if it has ::: no — instead parse by finding pattern "name(...)::Type" in string
        s = sprint(show, sig)
        # example s = "func1(x::Lena.I64, y::Lena.I64)::Lena.I64"
        if occursin("::", s)
            # split at last :: to get rettype
            idx = findlast("::", s)
            rettype_str = strip(s[idx+2:end])
            # build an expression of rettype from string:
            try
                ret_ann = Meta.parse(rettype_str)
            catch
                ret_ann = nothing
            end
        end
    end

    if ret_ann === nothing
        error("@lena: function must have explicit return type annotation, e.g. `::Lena.I64`")
    end

    # now collect arguments: need their names and their annotated types
    arg_syms = Symbol[]
    arg_type_exprs = Expr[]
    if sig isa Expr && sig.head == :call
        for a in sig.args[2:end]
            # each a expected like :(x::Lena.I64) or :x
            if a isa Expr && a.head == :(::)
                push!(arg_syms, a.args[1])
                push!(arg_type_exprs, a.args[2])
            elseif a isa Symbol
                push!(arg_syms, a)
                push!(arg_type_exprs, :(Any))  # no type annotation; unsupported
            else
                error("@lena: unsupported arg form: $a")
            end
        end
    end

    # map Lena types to Julia/C types
    c_arg_types = []
    for texpr in arg_type_exprs
        mapped = _map_lena_type_expr(texpr)
        push!(c_arg_types, mapped)
    end
    c_ret_type = _map_lena_type_expr(ret_ann)

    # Create new internal julia function name to avoid collision with ccallable name.
    jl_impl_name = Symbol("_jl_impl_", string(fname))

    # Build AST: define original function under jl_impl_name (with original arg names and original body & type annotations)
    # We'll construct an expression like:
    #   @eval begin
    #     $(Expr(:function, Expr(:call, jl_impl_name, sig.args[2:end]...), body))
    #     Base.@ccallable function $(fname)(args::Ctypes...)::Cret
    #         return $(jl_impl_name)(argnames...)
    #     end
    #   end
    # Need to reconstruct function signature for implementation:
    impl_sig_call = Expr(:call, jl_impl_name, [Expr(:kw, :__dummy, nothing)]...) # placeholder

    # build impl signature properly using the original argument expressions but replaced function name:
    impl_call = Expr(:call, jl_impl_name, sig.args[2:end]...)

    impl_func = Expr(:function, impl_call, body)

    # build ccallable arg list expression: (x::Int64, y::Int64)
    ccall_arg_pairs = []
    for (nm, t) in zip(arg_syms, c_arg_types)
        push!(ccall_arg_pairs, Expr(:(::), nm, t))
    end

    # build ccallable function signature expression
    ccall_sig_call = Expr(:call, fname, ccall_arg_pairs...)
    ccall_func = Expr(:block,
        :(Base.@ccallable function $(ccall_sig_call)::$(c_ret_type)
            return $(Expr(:call, jl_impl_name, arg_syms...))
        end)
    )

    # Finally wrap into @eval block and return escaped expression
    return quote
        # define the real implementation under a hidden name
        $(esc(impl_func))
        # define the ccallable forwarder (this will export a C ABI symbol with the name `$(String(fname))`)
        $(esc(ccall_func))
    end
end

end # module