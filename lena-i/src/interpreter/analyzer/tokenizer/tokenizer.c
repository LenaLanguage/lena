/* Include libraries */
#include <stdlib.h>
#include <stdint.h>

/* core */
#include "interpreter/core/lencoders/lencoder.h"

/* non-core */
#include "ltypes/lerror.h"
#include "ltypes/lchar.h"
#include "lmem/lmem.h"

/* interpreter */
#include "../config/conf_tokenizer.h"

/* tokenizer */
#include "tokenizer.h"

/* ---------------- FUNCTIONS ---------------- */

/* ---------------- HELPERS ---------------- */


#define LENA_ERROR_ADR LENA_TOKEN_ERROR_SYNTAX

static inline bool _is_token_valid(ltoken_buffer_t* buffer) {
	return (bool)(buffer->token[buffer->index].type < LENA_ERROR_ADR
		&& buffer->token[buffer->index].type != LENA_TOKEN_EOF);
}

static inline bool _is_trash(lchar_t sym) {
	return (bool)(sym == l(' ') || sym == l('\t'));
}

static inline bool _is_null(lchar_t sym) {
	return (bool)(sym == l('\0'));
}

/* token helpers */

/* ---------------- END OF FILE ---------------- */

#define LENA_EOF 0x02
static lerror_t _pass_trash_eof(lchar_t* input[], ltoken_buffer_t* buffer) {
	while (true) {
		if (_is_null(**input)) {
			buffer->token[buffer->index].type = LENA_TOKEN_EOF;
			buffer->token[buffer->index].data = NULL;
			buffer->token[buffer->index].len = 1;
			++(*input);
			return LENA_EOF;
		}
		if (!_is_trash((**input))) {
			return LENA_OK;
		}
		++(*input);
	}
}

/* ---------------- Non-simple operators (2 symbols) ---------------- */




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

static lerror_t _string_get_len(lchar_t* input[], size_t* restrict len) {
	/* Preparation */
	lchar_t* string = (*input);
	lchar_t separator = (*string);
	++string;

	/* Calculating */
	while ((*string) != separator) {               
		if (_is_null(*string)) {
			return LENA_ERROR;
		}

		/* Start analyzing \symbol */
		if ((*string) == l('\\')) {
			++string;
			if ((*string) == l('{')) {
				/* Like "\{0xff} ..." */
				do {
					++string;
					if (_is_null(*string)) {
						return LENA_ERROR;
					}
				} while ((*string) != l('}'));
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

static bool _is_string_sep(lchar_t sym) {
	return (bool)(sym == l('\'') || sym == l('\"'));
}

static lerror_t _encode_esc_string(lchar_t* input, lchar_t* restrict result, size_t* restrict counter) {
	size_t len = 0;
	lerror_t res = lencode_lchar(input, result, &len);
	if (res != LENA_ENCODE_SUCCESS_DEC) {
		len += 2;
	}
	(*counter) += len;
	return res;
}

static void _fill_string(lchar_t* restrict string, lchar_t* input[], size_t len) {
	/* pass ' or " */
	++(*input);
	size_t real_len = 0;
	/* 'i' for string, 'j' for input */
	for(size_t i = 0; i < len; ++i) {
		if ((*input)[real_len] == l('\\'))  {
			++real_len;
			if ((*input)[real_len] == l('{') ) {
				/* "\{0000}" "\"*/
				++real_len; /* pass { */
				lchar_t result = 0;
				_encode_esc_string((*input + real_len), &result, &real_len);
				string[i] = result;
				++real_len; /* pass } */
			} else {
				/* "\a" */
				string[i] = 0;
			}
		} else {
			string[i] = (*input)[real_len];
			++real_len;
		}
	}
	(*input) += real_len;
}

static void _token_string(lchar_t* input[], ltoken_buffer_t* buffer) {

	/* Calculating correct len of string */

	size_t len = 0;

	if (_string_get_len(input, &len) == LENA_ERROR) {
		buffer->token[buffer->index].type = LENA_TOKEN_ERROR_SYNTAX;
		buffer->token[buffer->index].data = (*input + 1) ;
		buffer->token[buffer->index].len = len;
		return;
	}

	lchar_t* string = lmalloc(len * sizeof(lchar_t));

	_fill_string(string, input, len);

	buffer->token[buffer->index].type = LENA_TOKEN_DATA_STRING;
	buffer->token[buffer->index].data = string;
	buffer->token[buffer->index].len = len;

	++(*input); /* pass last sep symbol */
}

/* ---------------- Simple tokens ---------------- */

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
extern bool _token_identifier(lchar_t* input[], ltoken_buffer_t* buffer);

static void _token_get_new(lchar_t* input[], ltoken_buffer_t* buffer) {

	/* Pass "trash" symbols */
	/* Terminate process if it's EOF */
	if (_pass_trash_eof(input, buffer) != LENA_OK) {
		return;
	}

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
			if ((**input) == l('\n')) {
				buffer->token[buffer->index].type = LENA_TOKEN_NEWLINE;
				buffer->token[buffer->index].data = NULL;
				buffer->token[buffer->index].len = 1;
				(*input)++;
			} else if (_is_string_sep((**input))) {
				/* If it's a string "string" */
				_token_string(input, buffer);
			} else if (is_ldigit((**input))) {
				/* If it's a digit */
				_token_number(input, buffer);
			} else if (is_lletter((**input))) {
				/* If it's an identifier */
				_token_identifier(input, buffer);
			} else {
				buffer->token[buffer->index].type = LENA_TOKEN_ERROR_INVALID_SYMBOL;
				buffer->token[buffer->index].data = (*input);
				buffer->token[buffer->index].len = 1;
				(*input)++;
			}
		}
	}

}

/* public */

lerror_t ltoken_buffer_init(ltoken_buffer_t* buffer) {
	ltoken_t* token_claster = lmalloc(LTTCS * sizeof(ltoken_t));
	/* size in bytes can be calculated like ^^^^^^^ */
	if (token_claster == NULL) {
		return LENA_ERROR;
	}
	buffer->len = LTTCS;
	buffer->token = token_claster;
	buffer->index = 0;
	return LENA_OK;
}

void ltoken_buffer_deinit(ltoken_buffer_t* buffer) {
	buffer->len = 0;
	free(buffer->token);
	buffer->index = 0;
}

void ltoken_get(lchar_t* input[], ltoken_buffer_t* buffer) {
	while (true) {
		_token_get_new(input, buffer);
		if (!_is_token_valid(buffer)) {
			buffer->index++;
			break;
		}
		buffer->index++;
	}
}
