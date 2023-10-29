#include <stdio.h>

int main() {
    int arrival_hour;
    int arrival_min;
    int depart_hour;
    int depart_min;
    int charge;
    int hours;
    int mins;

    printf("Enter arrival time: ");
    scanf(" %d %d", &arrival_hour, &arrival_min);

    printf("Enter departure time: ");
    scanf(" %d %d", &depart_hour, &depart_min);

    int totMin = (depart_hour - arrival_hour) * 60 + (depart_min - arrival_min);

    if (totMin <= 60) {
        charge = 3;
    } else if (totMin <= 120) {
        charge = 5;
    } else {
        charge = 5 + ((totMin - 120) / 60);
        if (charge > 15) {
            charge = 15;
        }
    }

    int tohr = totMin / 60;
    int tom = totMin % 60;
    printf("You parked %d hours and %d minutes.\n", tohr, tom);
    printf("Please pay %d dollars.\n", charge);

    return 0;
}