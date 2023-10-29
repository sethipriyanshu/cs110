#include <stdio.h>

int main(void) {
    int num;
    int dgcount[10] = {0};

    printf("Enter a number: ");
    scanf("%d", &num);
    while (num > 0) {
        int digit = num % 10;
        dgcount[digit]++;
        num /= 10;
    }

    int duplicateFound = 0;
    for (int i = 0; i < 10; i++) {
        if (dgcount[i] > 1) {
            duplicateFound = 1;
            break;
        }
    }

    if (duplicateFound) {
        printf("Duplicate digits found\n");
    } else {
        printf("No duplicate digits found\n");
    }

    return 0;
}
