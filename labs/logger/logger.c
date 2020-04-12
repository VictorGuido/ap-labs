#include <stdarg.h>
#include <stdio.h>
///#include "logger.h"




void textcolor(int attr, int fg, int bg) {	
    char command[13];
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg +30, bg + 40);
	printf("%s", command);
}

int printLabel(int bgColor, char* label) {
    textcolor(0, 0, bgColor);
	printf("%s", label);
	textcolor(0,7,0);
    printf(" ");
    return 0;
};

int infof(const char *format, ...) {
    printLabel(4,"INFO:");
    va_list arguments;
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
    return 0;	
}

int warnf(const char *format, ...) {
    printLabel(3,"WARNING:");
    va_list arguments;
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
    return 0;
}

int errorf(const char *format, ...) {
    printLabel(1,"ERROR:");
    va_list arguments;
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
    return 0;
}

int panicf(const char *format, ...) {
    printLabel(5,"PANIC:");
    va_list arguments;
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
    return 0;
}
