#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 51 // 50 characters + 1 for the null terminator

int main() {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int wordCount = 0;

    printf("Enter words (Ctrl-D to end):\n");

    while (wordCount < MAX_WORDS && scanf("%50s", words[wordCount]) != EOF) {
        // Increment wordCount to track the number of words entered
        wordCount++;
    }

    if (wordCount == 0) {
        printf("No words entered.\n");
    } else {
        printf("You entered the following words:\n");
        for (int i = 0; i < wordCount; i++) {
            printf("%d: %s\n", i + 1, words[i]);
        }
    }

    return 0;
}
