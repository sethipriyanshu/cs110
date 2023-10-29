#include <stdio.h>

int main(void)
{
    int startHour;
    int startMin;
    int endHour;
    int endMin;
    float dist;
    
    printf("Enter the start time: ");
    scanf("%d %d",&startHour,&startMin);
    printf("Enter the end time: ");
    scanf("%d %d",&endHour,&endMin);
    
    float hours = (endHour - startHour) + ((endMin - startMin) / 60.0);
    dist = hours * 4.0;
    printf("You have walked %.6f miles",dist);
}
