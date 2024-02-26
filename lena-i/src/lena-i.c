#include <lena-i.h>
#include <stdio.h>

lm lmain(lu32 argc, lc* argv[]) {
    lc* my_str = X"ФФФ";
    printf("%ld", lslen(my_str));
    lcout(my_str);
    range(i, 0, argc) {
        printf("%s\n", argv[i]);
    }
    return 0;
}
