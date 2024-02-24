#include <lena-i.h>

lm lmain(lu32 argc, lc* argv[]) {
    printf("Hello Lena! Again...");
    range(i, 0, argc) {
        printf("%s\n", argv[i]);
    }
    return 0;
}
