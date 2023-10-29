#include <string.h>
#include <stdio.h>

int main(void){
    char *words[10];
    int vals[10];
    int len;
    scanf("%d",&len);

    for(int i =0;i<len;i++){
        scanf("%s",&words[i]);
    }
    for(int i =0;i<len;i++){
        printf("%s",words[i]);
    }
}