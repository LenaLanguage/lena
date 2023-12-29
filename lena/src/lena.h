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


void kmp_table(char* sstr, size_t slen, int* table) {
    uint64_t pos = 2;
    uint64_t cnd = 0;
    table[0] = -1;
    table[1] = 0;
    while (pos < slen) {
        if (sstr[pos - 1] == sstr[cnd]) {
            cnd++;
            table[pos] = cnd;
            pos++;
        } else if (cnd > 0) {
            cnd = table[cnd];
        } else {
            table[pos] = 0;
            pos++;
        }
    }
}

uint32_t search_in_line(char* str, size_t len, char* sstr, size_t slen) {
    if (slen == 0) return 0;

    int* table = (int*)malloc(sizeof(int) * slen);
    if (!table) return UINT32_MAX;

    kmp_table(sstr, slen, table);

    uint64_t m = 0;
    uint64_t i = 0;
    while (m + i < len) {
        if (sstr[i] == str[m + i]) {
            if (i == slen - 1) {
                free(table);
                return m;
            }
            i++;
        } else {
            m += i - table[i];
            if (table[i] > -1) {
                i = table[i];
            } else {
                i = 0;
            }
        }
    }
    free(table);
    return UINT32_MAX;
}

char *std_libs[] = {"console", "os", "util", NULL};

#define LENA_SUCCESSFULLY       0
#define LENA_ITEM_NOT_EXISTS    1
#define LENA_ERROR              2

uint8_t import_function(char str[], size_t len) {
    uint32_t pos = search_in_line(str, len, (char *)"import", 6);
    uint32_t start_name = 0, end_name = 0;
    if (pos == UINT32_MAX){ return LENA_ITEM_NOT_EXISTS; }
    pos += 6;
    uint8_t slash_counter = 0;
    for(uint32_t i = 0; i < pos; ++i){
        if(str[i] == '/'){ ++slash_counter; } else { slash_counter = 0; }
        if(slash_counter == 2){
            return 1;
        }
    }
    slash_counter = 0;
    for(uint32_t i = pos; i < len; ++i){
        if(str[i] != ' ' && str[i] != '\t'){
            start_name = i;
            while(str[i] != ' ' && str[i] != '\t' && str[i] != '\n'){
                if(str[i] == '/'){ ++slash_counter; } else { slash_counter = 0; }
                if(slash_counter == 2){
                    /* NAME DOESN'T SET */
                    return LENA_ERROR;
                }
                ++i;
            }
            end_name = i;
            break;
        }
    }
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
        free(name_buffer);
    } else {
        /* NAME DOESN'T SET */
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
        if(import_function(buffer, clen) == LENA_ERROR){
           // printf("[%I64u]: Name doesn't set!", num_of_line);
        }
        // printf("%" PRIu64 "\n", search_in_line(buffer, clen, (char *)"console", 3));
    }
}

/* ******************************* FREE ******************************* */

#endif // __LENA_I__