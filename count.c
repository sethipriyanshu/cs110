#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *inputString = argv[1];
    int uppercaseCount = 0;
    int lowercaseCount = 0;
    int digitCount = 0;

    while (*inputString) {
        if (isupper(*inputString)) {
            uppercaseCount++;
        } else if (islower(*inputString)) {
            lowercaseCount++;
        } else if (isdigit(*inputString)) {
            digitCount++;
        }
        inputString++;
    }

    printf("Uppers = %d\n", uppercaseCount);
    printf("Lowers = %d\n", lowercaseCount);
    printf("Digits = %d\n", digitCount);

    return 0;
}
