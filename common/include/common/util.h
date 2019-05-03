#ifndef UTIL_H
#define UTIL_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/syslog.h>
#include <stdarg.h>

#define SYSLOG_TO_STDERR

typedef struct DataBlock
{
    uint64_t size;
    uint8_t * data;

} DataBlock;

long calc_file_size(FILE * fp);

void klog(int priority, const char *format, ...);

#endif // UTIL_H
