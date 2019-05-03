#include <common/util.h>

long calc_file_size(FILE * fp)
{
    // Save current file pointer position
    long current_pos = ftell(fp);

    fseek(fp, 0L, SEEK_END);
    long result = ftell(fp);

    // Return file pointer to original position
    fseek(fp, current_pos, SEEK_SET);

    return result;
}

void klog(int priority, const char *format, ...)
{
#ifdef SYSLOG_TO_STDERR
    va_list arglist;
    va_start(arglist, format );

    vfprintf(stderr, format, arglist );
    fprintf(stderr, "\n");

    va_end( arglist );
#else
    va_list arglist;
    va_start( arglist, format );

    vsyslog(priority, format, arglist);

    va_end( arglist );
#endif
}
