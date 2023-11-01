#include <stdio.h>

char *nums[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
char *tens[] = {"na", "na", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

void smallnum(FILE *fp, int n) {
    if (n >= 0 && n <= 19) {
        fprintf(fp, "%s", nums[n]);
    } else if (n >= 20 && n <= 99) {
        fprintf(fp, "%s", tens[n / 10]);
        if (n % 10 != 0) {
            fprintf(fp, "-%s", nums[n % 10]);
        }
    }
}

void printer_function(FILE *fp, int n) {
    if (n >= 0 && n <= 99) {
        smallnum(fp, n);
    } else if (n >= 100 && n <= 999) {
        fprintf(fp, "%s hundred", nums[n / 100]);
        if (n % 100 != 0) {
            fprintf(fp, " and ");
            smallnum(fp, n % 100);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *fp1, *fp2;
    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "w");

    if (fp1 == NULL || fp2 == NULL) {
        fprintf(stderr, "Error opening files.\n");
        return 1;
    }

    int n;
    while (fscanf(fp1, "%d", &n) != EOF) {
        printer_function(fp2, n);
        fprintf(fp2, "\n");
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
