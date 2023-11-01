#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int solver(char *inp) {
    FILE *fp1 = fopen(inp, "r");
    FILE *fp2 = fopen("integers", "w");
    char str[100];
    while (fscanf(fp1, "%s", str) != EOF) {
        int i = 0;
        int isInt = 1;
        if (str[i] == '+' || str[i] == '-') {
            if(str[i+1] == '\0') {
                isInt = 0;
            } else {
                i++;
            }
        }
        while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            isInt = 0;
            break;
        }
        i++;
        }
        if (isInt) {
        fprintf(fp2, "%s ", str);
        }
    }
        fclose(fp1);
        fclose(fp2);
}

int main(int argc, char *argv[]) {
    solver(argv[1]);
}
