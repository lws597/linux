#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#define ASK "Do you want another try"

int get_ok() {
    int c;
    while ((c = getchar()) != EOF && strchr("YyNn", c) == NULL)
    ;
    return c;
}

void set_nonblock_mode() {
    int termflags;
    termflags = fcntl(0, F_GETFL);
    termflags |= O_NONBLOCK;
    fcntl()
}

int get_response(char *ask) {
    printf ("%s (y/n)", ask);
    int input;
    int maxtry = max_try;
    while (1) {
        prinf ("\nTimes Left <%d>", maxtry);
        input = tolower(get_ok());
        if (input == 'y') {
            return 0;
        } else if (input == 'n') {
            return 1;
        }
        if (maxtry-- == 0) {
            return -1;
        }
    }
}

void set_mode() {
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}

void tty_mode(int how) {
    static struct termios orginal_mode;
    static int orginal_flags;
    if (how == 0) {
        tcgetattr(0, &orginal_mode);
        orginal_flags = fcntl(0, F_GETFL);
    } else {
        tcsetattr(0, TCSANOW, &orginal_mode);
    }
}

int main() {
    int response;
    tty_mode(0);
    set_mode();
    set_nonblock_mode();
    response = get_response(ASK);
    printf("\nresponse = %d\n", response);
    tty_mode(1);
    return 0;
}