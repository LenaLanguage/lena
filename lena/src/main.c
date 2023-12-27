#include "lena.h"

uint32_t search_in_line(char str[], size_t len, char sstr[], size_t slen){

}

void analize_code(FILE *src_fptr) {
    char buffer[SFMLL] = "";
    while(fgets(buffer, SFMLL, src_fptr) != NULL) {
        size_t clen = strlen(buffer);
        printf("%d\n", (int)clen);
    }
}

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
