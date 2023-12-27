#include "lena.h"

int main(int argc, char *argv[]){

    /* If Lena doesn't have any args */
    if (argc < 2){
        lena_no_input();
        exit(EXIT_SUCCESS);
    }

    FILE *fptr = NULL;
    fptr = fopen(argv[1], "r");
    analize_code(fptr);
    fclose(fptr);

    exit(EXIT_SUCCESS);
}
