#include <lena-i.h>

lm lmain(lu32 argc, lc* argv[]) {
    if (lcio_init() != L_OK) {
        lexit(L_EXIT_FAILURE);
    }
    lcout(X("世界你好莉娜！"));
    lcoutn(X("世界你好莉娜！"), 3);
    return 0;
}
