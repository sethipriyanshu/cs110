#include <stdio.h>

int main(void){
    int num_1;
    int num_2;
    int num_3;
    int num_4;
    float num_avg;
    printf("Enter four integers: ");
    scanf("%d %d %d %d",&num_1,&num_2,&num_3,&num_4);
    num_avg = (float)(num_1+num_2+num_3+num_4) / 4;
    printf("The average is %f",num_avg);
    return 0;
}