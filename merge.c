#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int num1;
    int num2;
    FILE *fp1;
    FILE *fp2;
    fp1 = fopen(argv[1], "r");
    if (fp1==NULL) {
        printf("Unable to open %s for reading\n", argv[1]);
        return 1;
    }
    fp2 = fopen(argv[2], "r");
    if (fp2==NULL) {
        printf("Unable to open %s for reading\n", argv[2]);
        return 1;
}
    fscanf(fp1,"%d",&num1);
    fscanf(fp2,"%d",&num2);
    while(!feof(fp1) && !feof(fp2)){
        if(num1<num2){
            printf("%d ",num1);
            fscanf(fp1,"%d",&num1);
        }
        else if(num1>num2){
            printf("%d ",num2);
            fscanf(fp2,"%d",&num2);
        }
        else{
            printf("%d ",num1);
            fscanf(fp1,"%d",&num1);
            fscanf(fp2,"%d",&num2);
        }

        }
    while(!feof(fp1)){
        printf("%d ",num1);
        fscanf(fp1,"%d",&num1);
    }
    while(!feof(fp2)){
        printf("%d ",num2);
        fscanf(fp2,"%d",&num2);
    }
    }
    

