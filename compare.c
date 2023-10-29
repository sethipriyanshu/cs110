#include <stdio.h>
#include <string.h>

int main(void){
    char str1[21];
    char str2[21];
    char str3[21];
    scanf("%s %s %s",&str1,&str2,&str3);
    if(strcmp(str1,str2)==0 && strcmp(str1,str3)==0 && strcmp(str2,str3)==0)
    {
        printf("All three are the same.");
    }
    else if(strcmp(str1,str2)==0 && strcmp(str2,str3)!=0 && strcmp(str1,str3)!=0){
        printf("Two of them are the same.");
    }
    else if(strcmp(str1,str2)!=0 && strcmp(str2,str3)==0 && strcmp(str1,str3)!=0){
        printf("Two of them are the same.");
    }
    else if(strcmp(str1,str2)!=0 && strcmp(str2,str3)!=0 && strcmp(str1,str3)==0){
        printf("Two of them are the same.");
    }
    else{
        printf("They are completely different.");
    }
}