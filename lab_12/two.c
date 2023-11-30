#include <stdio.h>

char minCharOfString(char *str) {
    if (*str == '\0') {
        return 127;
    } else {
        char minRest = minCharOfString(str + 1);
        return (*str < minRest) ? *str : minRest;
    }
}

char minCharOfStringArray(int num, char *array[]) {
    if (num == 0) {
        return 127; 
    } else {
        char minFirst = minCharOfString(array[0]);
        char minRest = minCharOfStringArray(num - 1, array + 1);
        return (minFirst < minRest) ? minFirst : minRest;
    }
}

int main(int argc, char *argv[]) {
    if (argc==1) {
        printf("%s requires at least one argument\n", argv[0]);
        return 1;
    }
    printf("The smallest character of all arguments is %c\n",
            minCharOfStringArray(argc-1, argv+1));
    return 0;
}