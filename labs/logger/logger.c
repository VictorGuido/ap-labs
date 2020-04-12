//Victor Jaret Guido Alvarado
//logger lib
#include <stdarg.h>
#include <stdio.h>


int infof(const char *format, ...) {
    //Set the label a background color
    printf("%c[%d;%d;%dm", 0x1B, 0, 30, 44);
    printf("%s", "INFO:");
    //Set the text a font color
    printf("%c[0;%d;%dm",0x1B, 36, 48);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    return 0;	
}

int warnf(const char *format, ...) {
    printf("%c[%d;%d;%dm", 0x1B, 0, 30, 43);
    printf("%s", "WARNING:");
    printf("%c[0;%d;%dm",0x1B, 33, 48);	 
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    return 1;
}

int errorf(const char *format, ...) {
    printf("%c[%d;%d;%dm", 0x1B, 0, 30, 41);
    printf("%s", "ERROR:");
    printf("%c[0;%d;%dm",0x1B, 31, 48);	
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    return 2;
}

int panicf(const char *format, ...) {
    printf( "%c[%d;%d;%dm", 0x1B, 0, 30, 45);
    printf("%s", "PANIC:");
    printf("%c[0;%d;%dm",0x1B, 35, 48);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    return 3;
}
