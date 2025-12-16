#include <stdio.h>

unsigned int countSteps(unsigned int n) {
    if (n <= 0) return -1;
    else if (n == 1) return 0;
    else if (n % 2 == 0) {
        return 1 + countSteps(n / 2);
    }
    else {
        return 1 + countSteps(3 * n + 1);
    }
}

int main() {
    unsigned int count = (countSteps(3));
    printf("%d\n", count);

    return 0;
}