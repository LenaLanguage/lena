/* lena_runtime.c - minimal runtime for cli functions used by codegen */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* str slice type aligned with LLVM %str_t = { i8*, i64 } */
typedef struct { char *ptr; long long len; } str_t;

/* print to stdout */
void lena_cli_out(char *p, long long len) {
    if (!p) return;
    /* write exact bytes (may contain NUL inside) */
    fwrite(p, 1, (size_t)len, stdout);
    fflush(stdout);
}

/* print to stderr */
void lena_cli_err(char *p, long long len) {
    if (!p) return;
    fwrite(p, 1, (size_t)len, stderr);
    fflush(stderr);
}

/* read into buffer and return str_t (caller expects aggregated return) */
str_t lena_cli_in_str(char *prompt, long long plen) {
    if (prompt && plen > 0) {
        fwrite(prompt, 1, (size_t)plen, stdout);
        fflush(stdout);
    }
    char buf[4096];
    if (!fgets(buf, sizeof(buf), stdin)) {
        str_t r = { NULL, 0 }; return r;
    }
    size_t l = strlen(buf);
    /* strip trailing newline? keep it—language can decide, here we remove newline */
    if (l > 0 && buf[l-1] == '\n') { buf[l-1] = '\0'; l--; }
    char *out = malloc(l + 1);
    memcpy(out, buf, l);
    out[l] = '\0';
    str_t r = { out, (long long)l };
    return r;
}

/* read integer (i32) */
int lena_cli_in_i32(char *prompt, long long plen) {
    if (prompt && plen > 0) { fwrite(prompt, 1, (size_t)plen, stdout); fflush(stdout); }
    char buf[64];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    return atoi(buf);
}

/* read integer (i64) */
long long lena_cli_in_i64(char *prompt, long long plen) {
    if (prompt && plen > 0) { fwrite(prompt, 1, (size_t)plen, stdout); fflush(stdout); }
    char buf[128];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    return atoll(buf);
}

/* flush: 1 => stdout, 2 => stderr */
void lena_cli_flush(int which) {
    if (which == 1) fflush(stdout);
    else if (which == 2) fflush(stderr);
}

/* Note: memory allocated by lena_cli_in_str.ptr must be freed by runtime user
   or by generated code that keeps ownership policy. For simplicity we leak it
   in this minimal runtime; for production you'd add allocation strategy. */
