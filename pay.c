#include <stdio.h>

int main(void){
    double wage;
    int hrs;
    scanf("%lf %d",&wage,&hrs);

    if(hrs<=40){
        printf("$%lf",wage*hrs);
    }
    else if(hrs<=50){
        double pay = (wage*40)+((hrs-40)*(1.5*wage));
        printf("$%lf",pay);
    }
    else{
        double pay = (wage*40)+(10*(1.5*wage))+((hrs-50)*(wage*2.0));
        printf("$%lf",pay);
    }
}