#include <stdio.h>

int main(void){
    int num;
    scanf("%d", &num);

    for (int i = 1; i <= num; i++) {
        printf("x");
    }
    printf("\n");

    for (int i = 2; i <= num - 1; i++) {
        printf("x");
        for (int j = 2; j <= num - 1; j++) {
            printf(" ");
        }
        printf("x\n");
    }

    if (num > 1) {
        for (int i = 1; i <= num; i++) {
            printf("x");
        }
        printf("\n");
    }

    return 0;
}
