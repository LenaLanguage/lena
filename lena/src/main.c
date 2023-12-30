#include "lena.h"

int main(int argc, char *argv[]){

    /* If Lena doesn't have any args */
    if (argc < 2){
        lena_no_input();
        exit(EXIT_FAILURE);
    }

    FILE *fptr = NULL;
    fptr = fopen(argv[1], "r");
    fclose(fptr);
    
    exit(EXIT_SUCCESS);
}




/*
    // Link modules

    char lena_path[LML];
    get_app_path(lena_path, LML);

    {
        int len = strlen(lena_path) - 1;
        for(int i = 0; i < 8; ++i){
            lena_path[len] = '\0';
            --len;
        }
    }
    
    char list_path[LML];

    strcpy(list_path, lena_path);
    strcat(list_path, "modules\\list.em");

    module_list_fptr = fopen(list_path, "r");
    if (module_list_fptr == NULL){
        printf("ERROR!");
    }
    
    // analize_code(fptr);

    char modules_path[LML];
    strcpy(modules_path, lena_path);
    strcat(modules_path, "modules\\");

    char buffer[SFMLL];
    uint64_t num_of_line = 0;
    while(fgets(buffer, SFMLL, module_list_fptr) != NULL) {
        char module_path[LML];
        strcpy(module_path, modules_path);
        strcat(module_path, buffer);

        {
            size_t n_index = strlen(module_path) - 1;
            if (module_path[n_index] == '\n'){
                module_path[n_index] = '\0';
            }
        }

        printf("File: %s\n", module_path);

        char cbuffer[SFMLL];
        FILE *cfptr = fopen(module_path, "r");
        if (cfptr == NULL){
            printf("ERROR!");
        }
        while(fgets(cbuffer, SFMLL, cfptr) != NULL) {
            printf("%s", cbuffer);
        }
        fclose(cfptr);
        printf("\n");
        ++num_of_line;
    }
    fclose(module_list_fptr);
*/
