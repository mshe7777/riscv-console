#include "include/utils.h"
#include "nanoprintf.h"


int line_printf(int idx, const char *format, ...)
{
    char *VIDEO_MEMORY = (char *)(0x50000000 + 0xF4800);
    unsigned int buff_len = 0x40;
    va_list args;
    int n = buff_len;
    va_start(args, format);
	// n = npf_vsnprintf(&VIDEO_MEMORY[idx], buff_len, format, args);
	va_end(args);

    return n;
}