/* Include libraries */
#include <stdlib.h>
#include <stdint.h>

/* non-core */
#include "ltypes/lchar.h"

/* interpreter */
#include "../config/conf_tokenizer.h"

/* tokenizer */
#include "tokenizer.h"

/* -------- Functions -------- */

/* private */

/* helpers */

static bool is_token_valid(ltoken_buffer_t* buffer) {
	return (bool)(buffer->token[buffer->index].type != LENA_TOKEN_ERROR_SYNTAX 
		&& buffer->token[buffer->index].type != LENA_TOKEN_EOF);
}

static bool is_trash(lchar_t sym) {
	return (bool)(sym == l(' ') || sym == l('\t'));
}

/* token helpers */

static void token_pass_trash(lchar_t* input[]) {
	while (is_trash((**input))) {
		++(*input);
	}
}

/* ---------------- token handlers ---------------- */

/* ---------------- String tokens ---------------- */

/**
 * "\x0000"
 * "\d0000"
 * "\o0000"
 * "\b0000"
 * 
 * "\n"
 * "\t"
 * "\\"
 * "\'"
 * "\""
*/

static bool is_esc_sym_divider(lchar_t sym) {
	return (sym == l('x') || sym == l('d')
			|| sym == l('o') || sym == l('b'));
}

static bool is_esc_sym(lchar_t sym) {
	return (sym == l('n') || sym == l('t')
			|| sym == l('a') || sym == l('r'));
}

static size_t __token_string_get_len(lchar_t* input[]) {
	
	lchar_t* string = (*input);

	lchar_t sep_sym = (*string);
	++string;

	size_t len = 0;
	bool is_islash = true;

	while ((*string) != sep_sym) {
		if ((*string) == l('\0')) {
			return 0;
		}

		if ((*string) == l('\\')) {
			/* If the next symbol is esc divider */
			if (is_esc_sym_divider(*(++string))) {
				/* like "\x{1000}" */
				if (*(++string) == l('{')) {
					while (*(++string) != l('}')) {
						if ((*string) == sep_sym) {
							goto syntax_error;
						}
					}
				} else {
					/* like "\x" */
					goto syntax_error;
				}
			} else if (is_esc_sym((*string))) {
				++len;
			}
			is_islash = true;
		} else {
			is_islash = false;
			++len;
		}

		++string; 
	}
	return len;

syntax_error:
	return 0;
}

static bool is_string_separator(lchar_t sym) {
	return (bool)(sym == l('\'') || sym == l('\"'));
}

static void __token_string(lchar_t* input[], ltoken_buffer_t* buffer) {
	
	printf("len = %ld\n", __token_string_get_len(input));

	lchar_t sep_sym = (**input);
	++(*input);

	lchar_t* str_start = (*input);
	size_t len = 0;
	bool is_islash = true;

	while ((**input) != sep_sym || is_islash) {
		if ((**input) == l('\0')) {
			buffer->token[buffer->index].type = LENA_TOKEN_ERROR_SYNTAX;
			return;
		}
		is_islash = ((**input) == l('\\'));
		++(*input); ++len;
	}

	buffer->token[buffer->index].type = LENA_TOKEN_DATA_STRING;
	buffer->token[buffer->index].data = (len > 0)? str_start : NULL;
	buffer->token[buffer->index].len = len;

	++(*input);
}

/* + it must be saved in another buffer with \x symbols */

/* ---------------- Simple tokens ---------------- */

/* -------- Private data type -------- */

typedef enum {

    /* Symbols */
    LENA_TOKEN_ST_COMMA = l(','),       /* , */
	LENA_TOKEN_ST_COLON = l(':'),		/* : */

    /* Comments */
    LENA_TOKEN_ST_C_SEMICOLON = l(';'),	/* ; */


    /* Arithmetic */
	LENA_TOKEN_ST_AC_EQU   	= l('='),    /* = */
	LENA_TOKEN_ST_AC_PLUS  	= l('+'),    /* + */
    LENA_TOKEN_ST_AC_MINUS 	= l('-'),    /* - */
    LENA_TOKEN_ST_AC_MUL   	= l('*'),    /* * */
    LENA_TOKEN_ST_AC_DIV   	= l('/'),    /* / */
    LENA_TOKEN_ST_AC_MOD   	= l('%'),    /* % */

    /* Binary */
    LENA_TOKEN_ST_BIN_NOT  	= l('!'),    /* ! */
    LENA_TOKEN_ST_BIN_AND  	= l('&'),    /* & */
    LENA_TOKEN_ST_BIN_OR   	= l('|'),    /* | */
    LENA_TOKEN_ST_BIN_XOR  	= l('^'),    /* ^ */

	/* Brackets */
	LENA_TOKEN_ST_SLBRACKET		= l('['),    /* [ */
    LENA_TOKEN_ST_SRBRACKET		= l(']'),    /* ] */
	LENA_TOKEN_ST_LPARENTHESIS	= l('('),    /* ( */
    LENA_TOKEN_ST_RPARENTHESIS	= l(')'),    /* ) */
	LENA_TOKEN_ST_LBRACE		= l('{'),	 /* { */
	LENA_TOKEN_ST_RBRACE		= l('}'),	 /* } */


} ltoken_stoken_list_t;

static const ltoken_type_t lookup_stoken_table[LCHAR_MAX + 1] = {
	/* Comma */
	[LENA_TOKEN_ST_COMMA]		= LENA_TOKEN_COMMA,

	/* Symbols */
	[LENA_TOKEN_ST_C_SEMICOLON] = LENA_TOKEN_C_SEMICOLON,
	[LENA_TOKEN_ST_COLON] 		= LENA_TOKEN_COLON,
	[LENA_TOKEN_ST_AC_EQU] 		= LENA_TOKEN_AC_EQU,

	/* Arithmetic */
	[LENA_TOKEN_ST_AC_PLUS]     = LENA_TOKEN_AC_PLUS,
	[LENA_TOKEN_ST_AC_MINUS]    = LENA_TOKEN_AC_MINUS,
	[LENA_TOKEN_ST_AC_MUL]      = LENA_TOKEN_AC_MUL,
	[LENA_TOKEN_ST_AC_DIV]      = LENA_TOKEN_AC_DIV,
	[LENA_TOKEN_ST_AC_MOD]      = LENA_TOKEN_AC_MOD,

	/* Binary */
	[LENA_TOKEN_ST_BIN_NOT]     = LENA_TOKEN_BIN_NOT,
	[LENA_TOKEN_ST_BIN_AND]     = LENA_TOKEN_BIN_AND,
	[LENA_TOKEN_ST_BIN_OR]      = LENA_TOKEN_BIN_OR,
	[LENA_TOKEN_ST_BIN_XOR]   	= LENA_TOKEN_BIN_XOR,

	/* Brackets */
	[LENA_TOKEN_ST_SLBRACKET]		= LENA_TOKEN_SLBRACKET,
	[LENA_TOKEN_ST_SRBRACKET]		= LENA_TOKEN_SRBRACKET,
	[LENA_TOKEN_ST_LPARENTHESIS] 	= LENA_TOKEN_LPARENTHESIS,
	[LENA_TOKEN_ST_LBRACE]			= LENA_TOKEN_LBRACE,
	[LENA_TOKEN_ST_RBRACE]			= LENA_TOKEN_RBRACE,
};

/* Macros to detect non-simple token */
#define LENA_TOKEN_NON_SIMPLE LENA_TOKEN_EOF

static ltoken_type_t _token_simple(lchar_t* input[], ltoken_buffer_t* buffer) {
	/* This function can recognize EOF Token */
	ltoken_type_t stoken_type = lookup_stoken_table[(int)(**input)];
	buffer->token[buffer->index].type = stoken_type;
	buffer->token[buffer->index].data = (*input);
	buffer->token[buffer->index].len = 1;
	if (stoken_type != LENA_TOKEN_NON_SIMPLE)
		++(*input);
	return stoken_type;
}

/* ---------------- Number tokens ---------------- */

#define LENA_TOKEN_INT_TO_DECIMAL(var) var+=(LENA_TOKEN_DATA_DECIMAL - LENA_TOKEN_DATA_INTEGER)

static void _token_number(lchar_t* input[], ltoken_buffer_t* buffer) {
	buffer->token[buffer->index].type = LENA_TOKEN_DATA_INTEGER;
	buffer->token[buffer->index].data = (*input);
	size_t len = 0;
	bool double_dot = false;
	while (is_ldigit((**input)) || (**input) == l('.')) {
		/* Check cases when number has more than 1 dot */
		if ((**input) == l('.')) {
            if (!double_dot) {
                double_dot = true;
                LENA_TOKEN_INT_TO_DECIMAL(buffer->token[buffer->index].type);
            } else {
                buffer->token[buffer->index].type = LENA_TOKEN_ERROR_SYNTAX;
                break;
            }
        }
		++(*input); ++len;
	}
	/* If the last symbol is '.' -> LENA_TOKEN_ERROR_SYNTAX */
	if ((*(*input - 1)) == l('.')) {
        buffer->token[buffer->index].type = LENA_TOKEN_ERROR_SYNTAX;
	}
	buffer->token[buffer->index].len = len;
}

/* ---------------- Identifer tokens ---------------- */

/* (from tokenizer_id.h) */

/* Helper function, for recognizing keywords */
extern bool __token_identifier(lchar_t* input[], ltoken_buffer_t* buffer);

static void _token_get_new(lchar_t* input[], ltoken_buffer_t* buffer) {

	/* Terminate process if it's EOF */
	if ((**input) == l('\0')) {
		buffer->token[buffer->index].type = LENA_TOKEN_EOF;
		buffer->token[buffer->index].data = (*input);
		buffer->token[buffer->index].len = 1;
		return;
	}

	/* Pass "trash" symbols */
	token_pass_trash(input);

	/* Recognize type of token */
	
	{
		/* Recognize simple tokens */
		if (_token_simple(input, buffer) != LENA_TOKEN_NON_SIMPLE) { 
			/* Terminate if it's simple token */
			return;
		} else {
			/* Recognize non-simple tokens */

			/* If it's a digit */
			if (is_string_separator((**input))) {
    			printf("String!\n");
				__token_string(input, buffer);
			} else if (is_ldigit((**input))) {
				_token_number(input, buffer);
			} else if (is_lletter((**input))) {
				/* If it's an identifier */
				__token_identifier(input, buffer);
			} else {
				buffer->token[buffer->index].type = LENA_TOKEN_KW_DEFAULT;
				buffer->token[buffer->index].data = (*input);
				buffer->token[buffer->index].len = 1;
				(*input)++;
			}
		}
	}

}

/* public */

bool ltoken_buffer_init(ltoken_buffer_t* buffer) {
	ltoken_t* token_claster = malloc(LTTCS * sizeof(ltoken_t));
	/* size in bytes can be calculated like ^^^^^^^ */
	if (token_claster == NULL) {
		return false;
	}
	buffer->len = LTTCS;
	buffer->token = token_claster;
	buffer->index = 0;
	return true;
}

void ltoken_buffer_deinit(ltoken_buffer_t* buffer) {
	buffer->len = 0;
	free(buffer->token);
	buffer->index = 0;
}

void ltoken_get(lchar_t* input[], ltoken_buffer_t* buffer) {
	while (true) {
		_token_get_new(input, buffer);
		if (!is_token_valid(buffer)) {
			buffer->index++;
			break;
		}
		buffer->index++;
	}
}
