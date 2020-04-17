//Victor Jaret Guido Alvarado
//Logger
#include "logger.h"

int main() {

    infof("%s\n", " General information: ");
    warnf("%s\n", " Communication between functions may cause an error");
    errorf(" %i %s\n", 404,"Grade not found");
    initLogger("stdout");
    infof("%s\n", " General information: ");
    warnf("%s\n", " Communication between functions may cause an error");
    errorf(" %i %s\n", 404,"Grade not found");


    initLogger("syslog");
    infof("%s\n", " General information: ");
    warnf("%s\n", " Communication between functions may cause an error");
    errorf(" %i %s\n", 404,"Grade not found");
    panicf(" %s\n", "WE ARE DOOMED!");

    return 0;
}
