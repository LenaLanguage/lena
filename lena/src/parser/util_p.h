#ifndef __UTIL_PARSER_H__
#define __UTIL_PARSER_H__

/* Util functions for LINA/LENA langs */

/* Path */

ssize_t get_app_path(char *path, int lenght){
#ifdef _WIN32
    ssize_t result;
    result = GetModuleFileName(NULL, path, lenght);
    if (result == 0){
        return -1;          /* UNIX STANDARD */
    } else {
        return result;
    }
#else
    return readlink("/proc/self/exe", path, lenght);
#endif
}

/* Strings */

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


#endif // __UTIL_PARSER_H__