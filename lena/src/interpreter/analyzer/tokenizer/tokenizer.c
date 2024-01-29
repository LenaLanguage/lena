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
		(*input)++;
	}
}

/* token handlers */

/* ---------------- Simple tokens ---------------- */

static const ltoken_type_t lookup_stoken_table[LCHAR_MAX + 1] = {
	/* Comma */
	[LENA_TOKEN_ST_COMMA]		= LENA_TOKEN_COMMA,

	/* Comments */
	[LENA_TOKEN_ST_C_SEMICOLON] = LENA_TOKEN_C_SEMICOLON,

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
		(*input)++;
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
		if ((**input) == l('.')) {
            if (!double_dot) {
                double_dot = true;
                LENA_TOKEN_INT_TO_DECIMAL(buffer->token[buffer->index].type);
            } else {
                buffer->token[buffer->index].type = LENA_TOKEN_ERROR_SYNTAX;
                break;
            }
        }
		putchar((**input));
		(*input)++; len++;
	}
	buffer->token[buffer->index].len = len;
}

/* ---------------- Identifer tokens ---------------- */

/* Helper function, for recognizing keywords */
extern bool __token_identifier_kw(lchar_t* input[], ltoken_buffer_t* buffer);

static void _token_identifier(lchar_t* input[], ltoken_buffer_t* buffer) {
	/* If it's not a keyword */
	if (!__token_identifier_kw(input, buffer)) {
		buffer->token[buffer->index].type = LENA_TOKEN_IDENTIFIER_GENERAL;
		buffer->token[buffer->index].data = (*input);
		size_t len = 0;
		while (is_lletter((**input))) {
			putchar((**input));
			(*input)++; len++;
		}
		buffer->token[buffer->index].len = len;
	}
}

void token_get_new(lchar_t* input[], ltoken_buffer_t* buffer) {

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
			if (is_ldigit((**input))) {
				_token_number(input, buffer);
			} else if (is_lletter((**input))) {
				/* If it's an identifier */
				_token_identifier(input, buffer);
			} else {
				buffer->token[buffer->index].type = LENA_TOKEN_KW_DEFAULT;
				buffer->token[buffer->index].data = (*input);
				buffer->token[buffer->index].len = 1;
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
		token_get_new(input, buffer);
		if (!is_token_valid(buffer)) {
			break;
		}
		buffer->index++;
	}
}
