#include <stdio.h>
#include <string.h>

int main(void)
{
    char opt;
    double income;
    double tax;

    while (100)
    {
        while (110)
        {
            printf("----------------------------------\n");
            printf("a. Single\n");
            printf("b. Married filing jointly\n");
            printf("c. Married filing separately\n");
            printf("d. Head of household\n");
            printf("e. Qualifying widow(er)\n");
            printf("----------------------------------\n");
            printf("Enter the filing status (a-e): ");
            scanf(" %c", &opt);

            if (opt == 'a' || opt == 'b' || opt == 'c' || opt == 'd' || opt == 'e')
            {
                break;
            }
            else
            {
                printf("Invalid filing status. Try again.\n");
            }
        }
        printf("Enter the estimated taxable income: ");
        scanf("%lf", &income);
        if (income < 0.0)
        {
            income = 0.0;
            printf("No negative income allowed. Income set to zero\n");
        }
        if (opt == 'a')
        {
            if (income <= 11000.00)
            {
                tax = 0.1 * income;
            }
            else if (income <= 44725.00)
            {
                tax = 1100.00 + (0.12 * (income - 11000.00));
            }
            else if (income <= 95375.00)
            {
                tax = 5147.00 + (0.22 * (income - 44725.00));
            }
            else if (income <= 182100.00)
            {
                tax = 16290.00 + (0.24 * (income - 95375.00));
            }
            else if (income <= 231250.00)
            {
                tax = 37104.00 + (0.32 * (income - 182100.00));
            }
            else if (income <= 578125.00)
            {
                tax = 52832.00 + (0.35 * (income - 231250.00));
            }
            else if (income > 578125.00)
            {
                tax = 174238.25 + (0.37 * (income - 578125.00));
            }
        }
        if (opt == 'b' || opt == 'e')
        {
            if (income <= 22000.00)
            {
                tax = 0.1 * income;
            }
            else if (income <= 89450.00)
            {
                tax = 2200.00 + (0.12 * (income - 22000.00));
            }
            else if (income <= 190750.00)
            {
                tax = 10294.00 + (0.22 * (income - 89450.00));
            }
            else if (income <= 364200.00)
            {
                tax = 32580.00 + (0.24 * (income - 190750.00));
            }
            else if (income <= 462500.00)
            {
                tax = 74208.00 + (0.32 * (income - 364200.00));
            }
            else if (income <= 693750.00)
            {
                tax = 105664.00 + (0.35 * (income - 462500.00));
            }
            else if (income > 693750.00)
            {
                tax = 186601.50 + (0.37 * (income - 693750.00));
            }
        }
        if (opt == 'c')
        {
            if (income <= 11000.00)
            {
                tax = 0.1 * income;
            }
            else if (income <= 44725.00)
            {
                tax = 1100.00 + (0.12 * (income - 11000.00));
            }
            else if (income <= 95375.00)
            {
                tax = 5147.00 + (0.22 * (income - 44725.00));
            }
            else if (income <= 182100.00)
            {
                tax = 16290.00 + (0.24 * (income - 95375.00));
            }
            else if (income <= 231250.00)
            {
                tax = 37104.00 + (0.32 * (income - 182100.00));
            }
            else if (income <= 346875.00)
            {
                tax = 52832.00 + (0.35 * (income - 231250.00));
            }
            else if (income > 346875.00)
            {
                tax = 93300.75 + (0.37 * (income - 346875.00));
            }
        }
        if (opt == 'd')
        {
            if (income <= 15700.00)
            {
                tax = 0.1 * income;
            }
            else if (income <= 59850.00)
            {
                tax = 1570.00 + (0.12 * (income - 15700.00));
            }
            else if (income <= 95350.00)
            {
                tax = 6868.00 + (0.22 * (income - 59850.00));
            }
            else if (income <= 182100.00)
            {
                tax = 14678.00 + (0.24 * (income - 95350.00));
            }
            else if (income <= 231250.00)
            {
                tax = 35498.00 + (0.32 * (income - 182100.00));
            }
            else if (income <= 578100.00)
            {
                tax = 51226.00 + (0.35 * (income - 231250.00));
            }
            else if (income > 578100)
            {
                tax = 172623.50 + (0.37 * (income - 578100.00));
            }
        }
        printf("The estimated tax is %lf\n", tax);
        char con[20];
        while (90)
        {
            
            printf("Continue with another taxpayer (yes or no)? ");
            scanf(" %s", &con);
            if (strcmp(con, "no") == 0 || strcmp(con, "yes") == 0)
            {
                break;
            }
            else
            {
                printf("Invalid answer. Try again.\n");
            }
        }
        if (strcmp(con, "no") == 0)
        {   printf("Goodbye.");
            break;
        }
    }

    return 0;
}
