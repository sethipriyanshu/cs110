#include <stdio.h>

int main(void){
    int num1 , num2 , num3 , num4 , num5;
    int max =0;
    int second_max = 0;
    printf("Enter five distinct positive integers: ");
    scanf("%d %d %d %d %d",&num1,&num2,&num3,&num4,&num5);

    int myarr[6] = {num1,num2,num3,num4,num5};

    for(int i=0;i<=4;i++){
        if(myarr[i]>max){
            max = myarr[i];
        }
    }
    for(int i=0;i<=4;i++){
        if(max == myarr[i]){
            myarr[i] = 0;
        }
    }
     for(int i=0;i<=4;i++){
        if(myarr[i]>second_max){
            second_max = myarr[i];
        }
    }

    printf("The second largest integer is %d",second_max);

}