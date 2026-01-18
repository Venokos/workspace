#include <stdio.h>

enum weekday {
    // mon, tue, wed, thur, fri, sat, sun
    mon = 1, tue, wed, thur, fri, sat, sun
};

typedef enum {
    first = 1, second, third
} number;

typedef enum {
    false, true
} bool;

int main() {
    enum weekday a;
    a = mon;
    enum weekday b;
    b = sun;

    printf("%d\n", a);
    printf("%d\n", b);

    number c = second;
    printf("%d\n", c);

    bool flag = false;
    if (flag) printf("true\n");
    else printf("false\n");
}