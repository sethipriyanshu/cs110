#include <stdio.h>
#include <stdbool.h>

int main() {
    int letterCount[26] = {0}; 
    int c;

    printf("Enter your input:\n");
    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z') {
            letterCount[c - 'a']++;
        }
    }

    bool missingLetters = false;
    printf("Missing letters: ");
    for (int i = 0; i < 26; i++) {
        if (letterCount[i] == 0) {
            missingLetters = true;
            putchar(i + 'a'); 
        }
    }

    if (!missingLetters) {
        printf("Your input contains all the letters\n");
    } else {
        printf("\n");
    }

    return 0;
}
