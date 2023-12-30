#ifndef __LENA_I__
#define __LENA_I__

/* Standard C libs */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

/* Standard LINA/LENA libraries */

/* Config */
#include "config/config.h"

/* STDOUT */
#include "stdout/stdout.h"

/* Errors and Warnings*/
#include "errors/errors.h"

/* Parser (Universal for LI/ENA family languages) */
#include "parser/parser.h"


/* ******************************* FREE ******************************* */

FILE *module_list_fptr = NULL;

uint8_t link_module(char *name, FILE *module_list) {
    
}

#define LENA_SUCCESSFULLY       0
#define LENA_ITEM_NOT_EXISTS    1
#define LENA_ERROR              2

uint8_t import_function(char str[], size_t len) {
    uint32_t pos = search_in_line(str, len, (char *)"import", 6);
    uint32_t start_name = 0, end_name = 0;
    if (pos == UINT32_MAX){ return LENA_ITEM_NOT_EXISTS; }
    pos += 6;

    /* Find comment sym before "import" -> "// import"*/
    uint8_t slash_counter = 0;
    for(uint32_t i = 0; i < pos; ++i){
        if(str[i] == '/'){ ++slash_counter; } else { slash_counter = 0; }
        if(slash_counter == 2){
            return LENA_ITEM_NOT_EXISTS;
        }
    }

    /* If comment wasn't found */
    slash_counter = 0;
    for(uint32_t i = pos; i < len; ++i){
        if(str[i] != ' ' && str[i] != '\t'){
            start_name = i;
            while(str[i] != ' ' && str[i] != '\t' && str[i] != '\n'){
                if(str[i] == '/'){ ++slash_counter; } else { slash_counter = 0; }
                if(slash_counter == 2){
                    /* NAME DOESN'T SET */
                    /* Comment before the name like "import //name "*/
                    return LENA_ERROR;
                }
                ++i;
            }
            end_name = i;
            break;
        }
    }

    /* If name exists */
    if (start_name != pos || end_name != pos){
        
        /* Creating a string from range */
        size_t cname_len = 0;
        char *name_buffer = malloc(sizeof(char) * (end_name - start_name));
        for(uint32_t i = start_name; i < end_name; ++i){
            name_buffer[cname_len] = str[i];
            ++cname_len;
        }
        name_buffer[cname_len] = '\0';
        
        /* Search string in list */
        /*
        {
            bool in_list = false;
            for(size_t i = 0; i < 2; ++i){
                if(strcmp(name_buffer, std_libs[i]) == 0){
                    in_list = true;
                    break;
                }
            }
            if(in_list == true){
                printf("%s - standard library\n", name_buffer);
            } else {
                printf("%s - unknown library!\n", name_buffer);
            }
        }
        */
        free(name_buffer);
    } else {
        /* NAME DOESN'T SET */
        /* like "import " (nothing) */
        return LENA_ERROR;
    }
    return LENA_SUCCESSFULLY;
}

void analize_code(FILE *src_fptr) {
    char buffer[SFMLL] = "";
    bool in_main_function = false;
    bool in_global_comment = false;
    uint64_t num_of_line = 0;
    while(fgets(buffer, SFMLL, src_fptr) != NULL) {
        ++num_of_line;
        size_t clen = strlen(buffer);
    }
}

/* ******************************* FREE ******************************* */

#endif // __LENA_I__