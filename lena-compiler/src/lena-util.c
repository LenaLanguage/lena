
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include <lena-util.h>

static int lena_log_enabled = 1; /* -1 = unknown, 0 = disabled, 1 = enabled */

void lena_log_init(void) {
    if (lena_log_enabled != -1) return;
    const char *env = getenv("LENA_LOG");
    if (env && strlen(env) > 0 && (env[0] != '0')) lena_log_enabled = 1;
    else lena_log_enabled = 0;
}

void lena_logf(const char *fmt, ...) {
    lena_log_init();
    if (!lena_log_enabled) return;
    va_list ap;
    va_start(ap, fmt);
    /* simple timestamp */
    time_t t = time(NULL);
    struct tm tm;
    localtime_s(&tm, &t);
    char ts[32];
    strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", &tm);
    fprintf(stderr, "[LENA %s] ", ts);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}
