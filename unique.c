#include <stdio.h>
#include <stdbool.h>

int main() {
    char input[51];
    int frequency[26] = {0};

    printf("Enter a string: ");
    scanf("%s", input);

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            frequency[input[i] - 'a']++;
        }
    }

    bool foundUnique = false;

    printf("Unique characters include: ");
    for (int i = 0; i < 26; i++) {
        if (frequency[i] == 1) {
            foundUnique = true;
            putchar(i + 'a');
            putchar(' ');
        }
    }

    if (!foundUnique) {
        printf("NONE\n");
    } else {
        printf("\n");
    }

    return 0;
}
