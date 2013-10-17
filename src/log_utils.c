#include "log_utils.h"
#include <stdio.h>
#include <stdarg.h>

void yarn_log_error(char* format, ...) {
    fprintf(stderr, "[ERROR] ");
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
}