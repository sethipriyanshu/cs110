#include <stdio.h>
#include <math.h>

int main(void){
    const int TWIZ_IN_PACK = 25;
    const int TWIZ_LEN_INCH = 7;
    int distance;
    int num_twiz;
    int num_pack;
    printf("Enter the distance between two cities in miles: ");
    scanf("%d",&distance);
    distance = distance*5280*12;

    num_twiz = distance / TWIZ_LEN_INCH;
    num_pack = num_twiz / TWIZ_IN_PACK;
    printf("You'll need %d packs\n",num_pack);
    return 0;
    

}