//Victor Jaret Guido Alvarado
//logger lib
#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>
#include "logger.h"

int syslogB=0;


int initLogger(char *logType) {
    if(strcmp(logType,"syslog") == 0){
        syslogB=1;
        printf("----Format pringting in SYSLOG-----");
    }
    if(strcmp(logType,"stdout") == 0){
        printf("----Format pringting in STDOUT-----\n");
    }
    return 0;
}

int infof(const char *format, ...) {
    //Set the label a background color
    printf("%c[%d;%d;%dm", 0x1B, 0, 30, 44);
    va_list args;
    va_start(args, format);
    if(syslogB){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_INFO, "INFO:", args);
        closelog();
        //printf("\nInfo has been written");
    }
    else{
        printf("%s", "INFO:");
    }
    //Set the text a font color
    printf("%c[0;%d;%dm",0x1B, 36, 48);
    if(syslogB){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_INFO, format, args);
        closelog();
        //printf("\nInfo has been written 2");
    }
    else{
        vprintf(format, args);
    }
    va_end(args);
    return 0;
}

int warnf(const char *format, ...) {
    printf("%c[%d;%d;%dm", 0x1B, 0, 30, 43);
    va_list args;
    if(syslogB){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_WARNING, "WARNING : ", args);
        closelog();
        //printf("\nwarning has been written");
    }
    else{
	  printf("%s", "WARNING:");
    }
    printf("%c[0;%d;%dm",0x1B, 33, 48);
    va_start(args, format);
    if(syslogB){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_WARNING, format, args);
        closelog();
        //printf("\nwarning has been written 2");
    }
    else{
        vprintf(format, args);
    }
    va_end(args);
    return 1;
}

int errorf(const char *format, ...) {
   printf("%c[%d;%d;%dm", 0x1B, 0, 30, 41);
   va_list args;
   if(syslogB){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_ERR, "ERROR :", args);
        closelog();
        //printf("\nError has been written");
    }
    else{
	  printf("%s", "ERROR:");
    }
    printf("%c[0;%d;%dm",0x1B, 31, 48);	
    va_start(args, format);
    if(syslogB){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_ERR, format, args);
        closelog();
        //printf("\nError has been written 2");
    }
    else{
        vprintf(format, args);
    }
    va_end(args);
    return 2;
}

int panicf(const char *format, ...) {
    printf( "%c[%d;%d;%dm", 0x1B, 0, 30, 45);
    va_list args;
    va_start(args, format);
    if(syslogB){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG, "PANIC :", args);
        closelog();
        //printf("\nPanic has been written ");
    }
    else{
	printf("%s", "PANIC:");
    }
    printf("%c[0;%d;%dm",0x1B, 35, 48);
    if(syslogB){
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG, format, args);
        closelog();
        //printf("\nPanic has been written 2");
    }
    else{
        vprintf(format, args);
        //raise(SIGABRT);
    }
    va_end(args);
    raise(SIGABRT);
    return 3;
}


