#include <stdio.h>
#include <ctype.h>

int main() {
    int vowelCounts[5] = {0}; // Array to store vowel counts (a, e, i, o, u)
    char word[51000]; // Array to store the current word
    int i, j;

    printf("Enter words (press Ctrl-D to end input):\n");

    while (scanf("%s", word) != EOF) {
        // Loop through each character in the word
        for (i = 0; word[i] != '\0'; i++) {
            char c = tolower(word[i]);
            // Check if the character is a vowel
            if (c == 'a') {
                vowelCounts[0]++;
            } else if (c == 'e') {
                vowelCounts[1]++;
            } else if (c == 'i') {
                vowelCounts[2]++;
            } else if (c == 'o') {
                vowelCounts[3]++;
            } else if (c == 'u') {
                vowelCounts[4]++;
            }
        }
    }

    printf("The vowel a occurred %d times\n", vowelCounts[0]);
    printf("The vowel e occurred %d times\n", vowelCounts[1]);
    printf("The vowel i occurred %d times\n", vowelCounts[2]);
    printf("The vowel o occurred %d times\n", vowelCounts[3]);
    printf("The vowel u occurred %d times\n", vowelCounts[4]);

    return 0;
}
