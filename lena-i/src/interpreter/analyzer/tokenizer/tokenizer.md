# Lena programming language -> Tokenizer

## [tokenizer.h](tokenizer.h) file

### Public types

`ltoken_type_t` - type of token

`ltoken_t` - token structure

`ltoken_buffer_t` - token buffer structure

### Public functions

`bool ltoken_buffer_init(ltoken_buffer_t* buffer)` - initialization

`void ltoken_buffer_deinit(ltoken_buffer_t* buffer)` - deinitialization

`void ltoken_get(lchar_t* input[], ltoken_buffer_t* buffer)` - get tokens to the structure

## [tokenizer.c](tokenizer.c) file

### Private types

`ltoken_t` - token structure

### Private functions

`void ltoken_get(lchar_t* input[], ltoken_buffer_t* buffer)` - get tokens to the structure
