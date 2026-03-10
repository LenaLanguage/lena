#include <stdlib.h>
#include <lena-compiler.h>
#include <lena-tokenizer.h>
#include <lena-ast.h>
#include <lena-codegen.h>
#include <lena-util.h>

int main(void) {

    lena_logf("main: starting compiler demo");

    const char* src =
        "main(argc:i32, argv:str[]):i32 {\n"
        "    cli::err(\"This is an error message!\\n\");\n"
        "    cli::out(\"This is a simple message!\\n\");\n"
        "    let number:i32 = cli::in(\"Put number here:\"):i32\n"
        "    let y_name:str = cli::in(\"Put your name here:\"):str\n"
        "    cli::flush(cli::stdout)\n"
        "    return 0\n"
        "}";

    token_list_t toks = tokenize(src);
    print_tokens(&toks);

    ast_node_t *ast = parse_program(&toks);
    if (!ast) { printf("AST parse failed\n"); return 1; }
    print_ast(ast, 0);

    lena_logf("main: emitting IR to output.ll");
    int r = codegen_emit_module(ast, "output.ll");
    printf("Codegen = %d\n", r);

    free_ast(ast);
    free_token_list(&toks);
    return 0;
}
