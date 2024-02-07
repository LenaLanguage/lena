/* Include libraries */
#include <stdlib.h>
#include <stdint.h>

/* non-core */
#include "ltypes/lerror.h"
#include "ltypes/lchar.h"
#include "lmem/lmem.h"

/* interpreter */
#include "../config/conf_tokenizer.h"

/* tokenizer */
#include "tokenizer.h"

/* -------------------------------- FUNCTIONS -------------------------------- */

/* ---------------- HELPERS ---------------- */

static inline bool is_token_valid(ltoken_buffer_t* buffer) {
	return (bool)(buffer->token[buffer->index].type != LENA_TOKEN_ERROR_SYNTAX 
		&& buffer->token[buffer->index].type != LENA_TOKEN_EOF);
}

static inline bool is_trash(lchar_t sym) {
	return (bool)(sym == l(' ') || sym == l('\t'));
}

static inline bool is_null(lchar_t sym) {
	return (bool)(sym == l('\0'));
}

/* token helpers */

static void token_pass_trash(lchar_t* input[]) {
	while (is_trash((**input))) {
		++(*input);
	}
}

/* -------------------------------- TOKEN HANDLERS -------------------------------- */


/* ---------------- END OF FILE ---------------- */

#define LENA_EOF 0x02

static inline lerror_t _token_eof(lchar_t* input[], ltoken_buffer_t* buffer) {
	if (is_null(**input)) {
		buffer->token[buffer->index].type = LENA_TOKEN_EOF;
		buffer->token[buffer->index].data = NULL;
		buffer->token[buffer->index].len = 1;
		return LENA_EOF;
	} else {
		return LENA_OK;
	}
}

/* ---------------- Non-simple operators ---------------- */

#define LENA_UNRECOGNIZED_TOKEN 0x03

static lerror_t _token_non_simple2(lchar_t* input[], ltoken_buffer_t* buffer) {
	lchar_t* input_ptr = (*input);
	ltoken_type_t type;
	switch ((*input_ptr)) {
		case l('<'): {
			++input_ptr;
			if ((*input_ptr) == l('-')) {
				type = LENA_TOKEN_LCONS;
			} else if ((*input_ptr) == l('<')) {
				type = LENA_TOKEN_LSTREAM;
			} else {
				type = LENA_TOKEN_ERROR_SYNTAX;
			}
			break;
		}
		case l('-'): {
			++input_ptr;
			if ((*input_ptr) == l('>')) {
				type = LENA_TOKEN_RCONS;
			} else {
				type = LENA_TOKEN_ERROR_SYNTAX;
			}
			break;
		}
		case l('>'): {
			++input_ptr;
			if ((*input_ptr) == l('>')) {
				type = LENA_TOKEN_RSTREAM;
			} else {
				type = LENA_TOKEN_ERROR_SYNTAX;
			}
			break;
		}
		default: {
			return LENA_UNRECOGNIZED_TOKEN;
		}
	}
	buffer->token[buffer->index].type = type;
	buffer->token[buffer->index].data = (*input);
	buffer->token[buffer->index].len = 2;
	(*input) += 2;
	return LENA_OK;
}


/* ---------------- String tokens ---------------- */

/**
 * "\{000}"
 * "\{0xFF}"
 * "\{0o377}"
 * "\{0b11111111}"
 * 
*/

static lerror_t __token_string_get_len(lchar_t* input[], size_t* restrict len) {
	/* Preparation */
	lchar_t* string = (*input);
	lchar_t separator = (*string);
	++string;

	/* Calculating */
	while((*string) != separator) {
		if (is_null(*string)) {
			return LENA_ERROR;
		}

		/* Start analyzing \symbol */
		if ((*string) == l('\\')) {
			++string;
			if ((*string) == l('{')) {
				/* Like "\{0xff} ..." */
				do {
					++string;
					if (is_null(*string)) {
						return LENA_ERROR;
					}
				} while((*string) != l('}'));
				/* Pass last '}' and inc len */
				++string;
				++(*len);
			} else {
				/* Like "\a ..." */
				/* Pass only one symbol */
				++string;
			}
		} else {
			/* Increment len */
			++string;
			++(*len);
		}
	}
	return LENA_OK;
}

static bool is_string_separator(lchar_t sym) {
	return (bool)(sym == l('\'') || sym == l('\"'));
}

/* only for __token_string_get_esc_sym */
#include <stdlib.h>

/* Inpermanent solution */
static lchar_t __token_string_get_esc_sym(lchar_t* restrict string) {
	lchar_t end;
	return wcstol(string, &end, 10);
}

static void __token_fill_string(lchar_t* restrict string, lchar_t* input[], size_t len) {
	for(size_t i = 0; i < len; ++i) {
		if (i[*input] == l('\\')) {
			i[string] = __token_string_get_esc_sym(string);
		} else {
			i[string] = i[*input];
		}
	}
}

static void __token_string(lchar_t* input[], ltoken_buffer_t* buffer) {

	/* Calculating correct len of string */

	size_t len = 0;

	if (__token_string_get_len(input, &len) == LENA_ERROR) {
		buffer->token[buffer->index].type = LENA_TOKEN_ERROR_SYNTAX;
		buffer->token[buffer->index].data = (*input + 1) ;
		buffer->token[buffer->index].len = len;
		return;
	}

	lchar_t* string = lmalloc(len * sizeof(lchar_t));
	__token_fill_string(string, input, len);

	buffer->token[buffer->index].type = LENA_TOKEN_DATA_STRING;
	buffer->token[buffer->index].data = string;
	buffer->token[buffer->index].len = len;
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

	/* Comparison */
    LENA_TOKEN_ST_CMP_G		= l('>'),       /* > */
    LENA_TOKEN_ST_CMP_L		= l('<'),       /* < */

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

	/* Comparison */
    [LENA_TOKEN_ST_CMP_G]		= LENA_TOKEN_CMP_G,
    [LENA_TOKEN_ST_CMP_L]		= LENA_TOKEN_CMP_L,

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
#define IS_LENA_TOKEN_SIMPLE(token) (token != LENA_TOKEN_EOF)
#define LENA_NO_SIMPLE_TOKEN 0x02

static lerror_t _token_simple(lchar_t* input[], ltoken_buffer_t* buffer) {
	/* This function can recognize EOF Token */
	ltoken_type_t type = lookup_stoken_table[(int)(**input)];
	buffer->token[buffer->index].type = type;
	buffer->token[buffer->index].data = (*input);
	buffer->token[buffer->index].len = 1;
	if (IS_LENA_TOKEN_SIMPLE(type)) {
		++(*input);
		/* Exception comment like "; comment" */
		if (type == LENA_TOKEN_C_SEMICOLON) {
			/* Pass comment */
			while ((**input) != l('\n') && (**input) != l('\0')){
				++(*input);
			}
		}
		return LENA_OK;
	}
	return LENA_NO_SIMPLE_TOKEN;
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
	if (_token_eof(input, buffer) != LENA_OK) {
		return;
	}

	/* Pass "trash" symbols */
	token_pass_trash(input);

	/* Recognize type of token */
	
	{

		/* for tokens like: << >> <- -> */
		if (_token_non_simple2(input, buffer) == LENA_OK) {
			/* Terminate if it's non-simple token */
			return;
		}

		/* Recognize simple tokens */
		if (_token_simple(input, buffer) != LENA_NO_SIMPLE_TOKEN) { 
			/* Terminate if it's simple token */
			return;
		} else {
			/* Recognize non-simple tokens */

			if (is_string_separator((**input))) {
				/* If it's a string "string" */
				__token_string(input, buffer);
			} else if (is_ldigit((**input))) {
				/* If it's a digit */
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
	ltoken_t* token_claster = lmalloc(LTTCS * sizeof(ltoken_t));
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
