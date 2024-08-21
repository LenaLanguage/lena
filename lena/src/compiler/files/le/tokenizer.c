/* Include specific libraries */
#include <compiler/files/le/tokenizer/tokenizer.h>

// debug only ->
#include <stdio.h>

/* ----------------  Tokens clasters ---------------- */
#define TOKEN_CLASTER_SIZE 128
#define TOKEN_GET_CLASTER(num) (lcalloc(TOKEN_CLASTER_SIZE * sizeof(le_token_t) * num, sizeof(le_token_t)))

/* ---------------- Trash characters ---------------- */
static const lc trash_chars[] = {
    (lc)(' '), (lc)('\t')
};
static lbool is_trash(lc ch) {
    for (lu8 i = 0; i < 2; ++i) {
        if (ch == trash_chars[i])
            return true;
    }
    return false;
}
static void pass_trash(lc** src_code) {
    while (is_trash(**src_code)) {
        (*src_code)++;
    }
}

/* ---------------- General macroses ---------------- */
#define IS_EOF(a) (a == (lc)('\0'))
#define IS_NUMBER_CHAR(a) ((lc)('0') <= a  && a <= (lc)('9'))
#define IS_IDENTIFIER_CHAR(a) (((lc)('a') <= a  && a <= (lc)('z'))\
    || ((lc)('A') <= a  && a <= (lc)('Z'))\
    || ((lc)('_') == a))
#define IS_UNRECOGNIZED_TOKEN(a) (lbool)(a.size == 0)
#define TOKEN_DEFAULT {LE_TOKEN_SYNTAX_ERROR, NULL, 0}

/* Constants */
static const lc* msg_invalid_decimal_str = X("Incorrect decimal notation, more than one point used.");

/* ---------------- One-byre tokens ---------------- */

static const lc token_onebyte_map[] = {
    [LE_TOKEN_ONE_COMMENT]  = (lc)(';'),

    [LE_TOKEN_MATH_EQU]     = (lc)('='),

    [LE_TOKEN_MATH_PLUS]    = (lc)('+'),
    [LE_TOKEN_MATH_MINUS]   = (lc)('-'),
    [LE_TOKEN_MATH_MUL]     = (lc)('*'),
    [LE_TOKEN_MATH_DIV]     = (lc)('/'),

    [LE_TOKEN_MATH_MOD]     = (lc)('%'),

    [LE_TOKEN_CMP_G]        = (lc)('>'),
    [LE_TOKEN_CMP_L]        = (lc)('<'),

    [LE_TOKEN_SLBRACKET]      = (lc)('['),
    [LE_TOKEN_SRBRACKET]      = (lc)(']'),
    [LE_TOKEN_LPARENTHESIS]   = (lc)('('),
    [LE_TOKEN_RPARENTHESIS]   = (lc)(')'),
    [LE_TOKEN_LBRACE]         = (lc)('{'),
    [LE_TOKEN_RBRACE]         = (lc)('}'),

    [LE_TOKEN_COLON]         = (lc)(':'),
    [LE_TOKEN_PERIOD]        = (lc)('.'),
    [LE_TOKEN_COMMA]         = (lc)(','),

};
static le_token_t token_onebyte_get(lc** src_code) {
    static le_token_t token = TOKEN_DEFAULT;
    for (lu8 i = LE_TOKEN_ONE_BYTE_BEGIN; 
        i <= LE_TOKEN_ONE_BYTE_END; ++i) {
        // printf("check... %d with %d\n", token_onebyte_map[i], (**src_code));
        if (token_onebyte_map[i] == (**src_code)) {
            token.type = (le_token_type_t)(i);
            token.size = 1;
            (*src_code)++;
            return token;
        }
    }
    return token;
}

/* ---------------- Multi-byte tokens ---------------- */
static const lc* token_multibyte_map[] = {

    /* Constructions */

    [LE_TOKEN_MULTILINE_COMMENT_L]  (X("/*")),
    [LE_TOKEN_MULTILINE_COMMENT_R]  (X("*/")),

    [LE_TOKEN_MATH_CDIV]            (X("//")),

    [LE_TOKEN_MATH_PLUS_EQ]         (X("+=")),
    [LE_TOKEN_MATH_MINUS_EQ]        (X("-=")),
    [LE_TOKEN_MATH_MUL_EQ]          (X("*=")),
    [LE_TOKEN_MATH_DIV_EQ]          (X("/=")),
    [LE_TOKEN_MATH_CDIV_EQ]         (X("//=")),
    [LE_TOKEN_MATH_MOD_EQ]          (X("%=")),

    [LE_TOKEN_CMP_E]                (X("==")),
    [LE_TOKEN_CMP_GE]               (X(">=")),
    [LE_TOKEN_CMP_LE]               (X("<=")),

    /* Words */

    [LE_TOKEN_LOGIC_IF]             (X("if")),
    [LE_TOKEN_LOGIC_ELSE]           (X("else")),
    [LE_TOKEN_LOGIC_ELIF]           (X("elif")),

    [LE_TOKEN_LOGIC_NOT]            (X("not")),
    [LE_TOKEN_LOGIC_AND]            (X("and")),
    [LE_TOKEN_LOGIC_OR]             (X("or")),
    [LE_TOKEN_LOGIC_XOR]            (X("xor")),

    [LE_TOKEN_ID_DTYPE_BOOL]        (X("bool")),

    [LE_TOKEN_ID_DTYPE_I8]          (X("i8")),
    [LE_TOKEN_ID_DTYPE_U8]          (X("u8")),
    [LE_TOKEN_ID_DTYPE_I16]         (X("i16")),
    [LE_TOKEN_ID_DTYPE_U16]         (X("u16")),
    [LE_TOKEN_ID_DTYPE_I32]         (X("i32")),
    [LE_TOKEN_ID_DTYPE_U32]         (X("u32")),
    [LE_TOKEN_ID_DTYPE_I64]         (X("i64")),
    [LE_TOKEN_ID_DTYPE_U64]         (X("u64")),

    [LE_TOKEN_ID_DTYPE_F32]         (X("f32")),
    [LE_TOKEN_ID_DTYPE_F64]         (X("f64")),

    [LE_TOKEN_IDENTIFIER_DTYPE_STR] (X("str")),
    [LE_TOKEN_IDENTIFIER_DTYPE_CHAR](X("char")),

    [LE_TOKEN_KW_TRUE]              (X("true")),
    [LE_TOKEN_KW_FALSE]             (X("false")),
};
// (without '\0')
static const lsz token_multibyte_size_map[] = {

    [LE_TOKEN_MULTILINE_COMMENT_L]  (2),
    [LE_TOKEN_MULTILINE_COMMENT_R]  (2),

    [LE_TOKEN_MATH_CDIV]            (2),

    [LE_TOKEN_MATH_PLUS_EQ]         (2),
    [LE_TOKEN_MATH_MINUS_EQ]        (2),
    [LE_TOKEN_MATH_MUL_EQ]          (2),
    [LE_TOKEN_MATH_DIV_EQ]          (2),
    [LE_TOKEN_MATH_CDIV_EQ]         (2),
    [LE_TOKEN_MATH_MOD_EQ]          (2),

    [LE_TOKEN_CMP_E]                (2),
    [LE_TOKEN_CMP_GE]               (2),
    [LE_TOKEN_CMP_LE]               (2),

    [LE_TOKEN_LOGIC_IF]             (2),
    [LE_TOKEN_LOGIC_ELSE]           (4),
    [LE_TOKEN_LOGIC_ELIF]           (4),

    [LE_TOKEN_LOGIC_NOT]            (3),
    [LE_TOKEN_LOGIC_AND]            (3),
    [LE_TOKEN_LOGIC_OR]             (2),
    [LE_TOKEN_LOGIC_XOR]            (3),

    [LE_TOKEN_ID_DTYPE_BOOL]        (4),

    [LE_TOKEN_ID_DTYPE_I8]          (2),
    [LE_TOKEN_ID_DTYPE_U8]          (2),
    [LE_TOKEN_ID_DTYPE_I16]         (3),
    [LE_TOKEN_ID_DTYPE_U16]         (3),
    [LE_TOKEN_ID_DTYPE_I32]         (3),
    [LE_TOKEN_ID_DTYPE_U32]         (3),
    [LE_TOKEN_ID_DTYPE_I64]         (3),
    [LE_TOKEN_ID_DTYPE_U64]         (3),

    [LE_TOKEN_ID_DTYPE_F32]         (3),
    [LE_TOKEN_ID_DTYPE_F64]         (3),

    [LE_TOKEN_IDENTIFIER_DTYPE_STR] (3),
    [LE_TOKEN_IDENTIFIER_DTYPE_CHAR](4),

    [LE_TOKEN_KW_TRUE]              (4),
    [LE_TOKEN_KW_FALSE]             (5),
};
static le_token_t token_multibyte_get(lc** src_code, lbool words) {
    static le_token_t token = {LE_TOKEN_IDENTIFIER_UNDEF, NULL, 0};
    
    static lu8 low_limit, high_limit;

    if (words) {
        low_limit   = LE_TOKEN_LOGIC_IF;
        high_limit  = LE_TOKEN_MULTI_BYTE_END;
    } else {
        low_limit   = LE_TOKEN_MULTI_BYTE_BEGIN;
        high_limit  = LE_TOKEN_LOGIC_IF;
    }
    
    for (lu8 i = low_limit; i <= high_limit; ++i) {
        if (!lmemcmp(token_multibyte_map[i], (*src_code), token_multibyte_size_map[i])) {
            token.size = token_multibyte_size_map[i];
            token.type = (le_token_type_t)(i);
            // pass this identitier
            (*src_code) += token_multibyte_size_map[i];
            return token;
        }
    }
    token.size = 0;
    return token;
}

/* ---------------- Undef-byte tokens ---------------- */
static le_token_t token_undefbyte_get(lc** src_code) {
    le_token_t token = {LE_TOKEN_SYNTAX_ERROR, NULL, 0};
    token.value = (*src_code);
    token.type = LE_TOKEN_IDENTIFIER_UNDEF;

    /* After first character it can be a number */
    do {
        token.size++;
        (*src_code)++;
    } while(IS_IDENTIFIER_CHAR((**src_code)) 
        || IS_NUMBER_CHAR((**src_code)));
    return token;
}

/* ---------------- Numbers ---------------- */
static le_token_t token_number_get(lc** src_code) {
    le_token_t token = {LE_TOKEN_SYNTAX_ERROR, NULL, 0};
    
    token.value = (*src_code);
    token.type = LE_TOKEN_INTEGER;

    lbool is_decimal = false;

    do {
        if ((**src_code) == (lc)('.')) {
            if (is_decimal == true) {
                token.type = LE_TOKEN_SYNTAX_ERROR;
                token.value = (lc*)(msg_invalid_decimal_str);
                token.size = 0;
                return token;
                // more than one '.'
            } else {
                token.type = LE_TOKEN_DECIMAL;
            }
        } else if (!IS_NUMBER_CHAR((**src_code))) {
            token.type = LE_TOKEN_INVALID_CHARACTER;
            token.value = (*src_code);
            token.size = 1;
            return token;
        }
        token.size++;
        (*src_code)++;
    } while ((**src_code) == (lc)('.') || IS_NUMBER_CHAR((**src_code)));
    
    return token;
}

/* ---------------- Strings and characters ---------------- */
#define IS_STRING_BEGIN(character) (lbool)((character) == (lc)('\"'))
static le_token_t token_string_get(lc** src_code) {
    le_token_t token = {LE_TOKEN_SYNTAX_ERROR, NULL, 0};
    (*src_code)++; // pass first '\"'
    token.value = (*src_code);
    // будешь добавлять сообщения об ошибках? -> да
    do {
        token.size++;
        (*src_code)++;
        if (IS_EOF((**src_code))){
            token.size = 0;
            return token;
        }
    } while ((**src_code) != (lc)('\"'));
    token.type = LE_TOKEN_STRING;
    (*src_code)++; // pass last '\"'
    return token;
}
#define IS_CHARACTER_BEGIN(character) (lbool)((character) == (lc)('\''))
static le_token_t token_character_get(lc** src_code) {
    le_token_t token = {LE_TOKEN_SYNTAX_ERROR, NULL, 0};
    (*src_code)++; // pass first '\''
    token.value = (*src_code);
    do {
        token.size++;
        (*src_code)++;
        if (IS_EOF((**src_code))) {
            token.size = 0;
        }
    } while((**src_code) != (lc)('\''));
    (*src_code)++; // pass last '\''
    return token;
}

/* ---------------- NEWLINE token ---------------- */
#define IS_NEWLINE(str) (lbool)(((*str) == (lc)('\r') && ((*(str + 1)) == (lc)('\n'))) || (*str) == (lc)('\n'))
static le_token_t token_newline_get(lc** src_code){
    static le_token_t token = {LE_TOKEN_NEWLINE, NULL, 0};
    /* Check CRLF */
    if ((**src_code) == (lc)('\r') && (*(*src_code+1) == (lc)('\n'))) {
        (*src_code) += 2;
        token.size = 2;
    } else if ((**src_code) == (lc)('\n')) {
        /* Check LF */
        (*src_code)++;
        token.size = 1;
    } else {
        token.size = 0;
    }
    return token;
}

/*

Надо переписать Лену....

[.]
|  \____+   
|+      |
|    @  |
[+]-----+
\
 \=         |
  \         |
    [+=] ---+

*/

/* ---------------- Comments token ---------------- */
static void pass_comments(lc** src_code, le_token_type_t prev_token_type) {

    /* Pass everything until NEWLINE token */
    if (prev_token_type == LE_TOKEN_ONE_COMMENT) {
        do {
            (*src_code)++;
            if (IS_EOF((**src_code))){
                return;
            }
        } while (!IS_NEWLINE((*src_code)));
        return;
    }

    /* Pass everything until LE_TOKEN_MULTILINE_COMMENT_R token */
    if (prev_token_type == LE_TOKEN_MULTILINE_COMMENT_L) {
        do {
            (*src_code)++;
            if (IS_EOF((**src_code))){
                return;
            }
        } while (!!lmemcmp(
            token_multibyte_map[LE_TOKEN_MULTILINE_COMMENT_R], 
            (*src_code), 
            token_multibyte_size_map[LE_TOKEN_MULTILINE_COMMENT_R]
            ));
        return;
    }
}

/* ---------------- EOF token ---------------- */
static const le_token_t token_eof = {LE_TOKEN_EOF, NULL, 0};

/* ---------------- BIG FUNCTIONS ---------------- */

static lerr token_expand_buffer(le_token_buffer_t* buffer) {
    if (buffer->i >= buffer->num) {
        le_token_t* new_tokens = lrealloc(buffer->token, 
            (buffer->num * sizeof(le_token_t)) 
                + TOKEN_CLASTER_SIZE * sizeof(le_token_t));
    
        if (lmemchk(new_tokens) == L_ERROR_MALLOC) {
            return L_ERROR_MALLOC;
        }
        buffer->token = new_tokens;
        buffer->num += TOKEN_CLASTER_SIZE;
    }
}

static le_token_t token_handler(lc** src_code, lbool newline, lu64* loc) {
    static le_token_t token;
    begin_handle:{
        /* ---------- NEWLINE ---------- */
        token = token_newline_get(src_code);
        if (!IS_UNRECOGNIZED_TOKEN(token)){
            printf("The newline identifier...\n");
            if (!newline) {
                (*loc)++;
                return token;
            } else {
                /* Pass several NEWLINE tokens */
                // we do not need to create a new token for each newline...
                (*loc)++;
                goto begin_handle;
            }
        }

        /* ---------- NUMBERS ---------- */

        /* ----- can return an error */
        if (IS_NUMBER_CHAR((**src_code))) {
            printf("The number...\n");
            token = token_number_get(src_code);
            return token;
        }

        /* ---------- STRINGS AND CHARS ---------- */

        /* ----- can return an error */
        if (IS_STRING_BEGIN((**src_code))) {
            token = token_string_get(src_code);
            return token;
        }

        /* ----- can return an error */
        if (IS_CHARACTER_BEGIN((**src_code))) {
            token = token_character_get(src_code);
            return token;
        }


        /* ---------- IDENTIFIERS ---------- */

        /* ----- can return an error */
        if (IS_IDENTIFIER_CHAR((**src_code))) {
            printf("The identifier...\n");
            token = token_multibyte_get(src_code, true);
            if (!IS_UNRECOGNIZED_TOKEN(token)) {
                return token;
            }
            printf("The undef identifier...\n");
            token = token_undefbyte_get(src_code);
            return token;
        } 

        /* ---------- CHARACTERS ---------- */

        token = token_multibyte_get(src_code, false);
        if (!IS_UNRECOGNIZED_TOKEN(token)) {
            printf("The multi-byte identifier...\n");
            return token;
        }

        token = token_onebyte_get(src_code);
        if (!IS_UNRECOGNIZED_TOKEN(token)) {
            printf("The one-byte identifier...\n");
            return token;
        }

        /* ---------- ERROR ---------- */

    }
}

/* Public functions */
lerr le_token_get(lc* src_code, le_token_buffer_t* buffer) {
    
    /* Initialize token buffer */
    buffer->num     = TOKEN_CLASTER_SIZE;   // theoretical numbers of tokens
    buffer->i       = 0;                    // real numbers of tokens
    buffer->token   = TOKEN_GET_CLASTER(1); // data buffer
    buffer->loc     = 1;                    // lines of code

    lbool is_newline = false;

    while (!IS_EOF((*src_code))){

        /* Expand buffer of tokens */
        if (token_expand_buffer(buffer) == L_ERROR_MALLOC){
            return L_ERROR_MALLOC;
        }

        /* Token handler reads only ONE token */
        buffer->token[buffer->i] = token_handler(&src_code, is_newline, &(buffer->loc));
        is_newline = (lbool)(buffer->token[buffer->i].type == LE_TOKEN_NEWLINE);

        printf(
            "type = %d size = %d value = %s\n", 
            buffer->token[buffer->i].type, 
            buffer->token[buffer->i].size,
            buffer->token[buffer->i].value
        );

        /* Pass commentary */
        pass_comments(&src_code, buffer->token[buffer->i].type);

        buffer->i++;

        /* Pass useless symbols */
        pass_trash(&src_code);

    }

    printf("\n\n--> Final size: takes %d tokens, real %d tokens.", buffer->num, buffer->i);
    printf("\n---> lines of code: %d", buffer->loc);
}