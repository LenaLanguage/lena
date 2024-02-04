
/* EXPERIMENTAL ALGHORITM FOR FAST STRCPY */

#include <lena.h>

/* 0.5 Gb */
#define VL_SIZE 536870912

lchar_t* very_longstr;
lchar_t* very_longstr2;

LMAIN(LENA_ARGC, LENA_ARGV){
    if(!lstd_init()){ lexit(LENA_EXIT_FAILURE); };
    
    very_longstr = calloc(VL_SIZE, sizeof(lchar_t));
    memset(very_longstr, l('a'), sizeof(lchar_t));

    very_longstr2 = malloc(VL_SIZE);
    
    
    
    {
        size_t len = VL_SIZE;
        len /= sizeof(int64_t);
        size_t shift = 0;
        
        for (uint64_t i = 0; i < len; ++i) {
            (*(int64_t*)(very_longstr2 + shift)) = (*(int64_t*)(very_longstr + shift));
            shift += sizeof(int64_t);
        }
    }
    
    
    
    //memcpy(very_longstr2, very_longstr, VL_SIZE);

    free(very_longstr);
    free(very_longstr2);
    lexit(LENA_EXIT_SUCCESS);
    return 0;
}
