#include <stdio.h>
#include <math.h>

int main(void){
    int num_quarters, num_dimes, num_nickels, num_pennies;
    printf("Enter the number of quarters: ");
    scanf("%d",&num_quarters);
    printf("Enter the number of dimes: ");
    scanf("%d",&num_dimes);
    printf("Enter the number of nickels: ");
    scanf("%d",&num_nickels);
    printf("Enter the number of pennies: ");
    scanf("%d",&num_pennies);

    int dollar_value = ((num_quarters*25)+(num_dimes*10)+(num_nickels*5)+(num_pennies*1)) / 100;
    int cent_value = ((num_quarters*25)+(num_dimes*10)+(num_nickels*5)+(num_pennies*1)) % 100;
    printf("Total value is %d dollars and %d cents.\n",dollar_value,cent_value);

    double coin_weight = ((num_quarters*5.67)+(num_dimes*2.268)+(num_nickels*5.0)+(num_pennies*2.5))*0.00220462;
    printf("Total weight of coins is %lf pounds.\n",coin_weight);

    int num_barrows = ceil(coin_weight/300);
    printf("It needs %d wheelbarrows to transport the coins.\n",num_barrows);

    printf("%d dollars of coins can be exchanged for the following paper bills:\n",dollar_value);

    int twenty_bills = dollar_value / 20;
    dollar_value = dollar_value - (twenty_bills*20);
    int ten_bills = dollar_value / 10;
    dollar_value = dollar_value - (ten_bills*10);
    int five_bills = dollar_value / 5;
    dollar_value = dollar_value - (five_bills*5);
    int one_bills = dollar_value / 1;

    printf("        %d twenty-dollar bills\n",twenty_bills);
    printf("        %d ten-dollar bills\n",ten_bills);
    printf("        %d five-dollar bills\n",five_bills);
    printf("        %d one-dollar bills\n",one_bills);

    int total_bills = twenty_bills+ten_bills+one_bills+five_bills;
    double bill_weight = total_bills * 0.00220462;
    printf("The weight of paper bills is only %lf pounds.\n",bill_weight);
    return 0;
    
}