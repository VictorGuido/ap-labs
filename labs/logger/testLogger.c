//Victor Jaret Guido Alvarado
//Test Logger

int infof(const char *format, ...);

int warnf(const char *format, ...);

int errorf(const char *format, ...);

int panicf(const char *format, ...);

int main() {

    infof("%s\n", " General information: ");
    warnf("%s\n", " Warning: Communication between functions may cause an error");
    errorf(" %i %s\n", 404,"Grade not found");
    panicf(" %s\n", "WE ARE DOOMED!");

    return 0;
}
