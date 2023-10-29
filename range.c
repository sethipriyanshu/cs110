#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("This program requires at least one argument");
        return 1;
    }

    double max = atof(argv[1]);
    double min = atof(argv[1]);

    for (int i = 2; i < argc; i++) {
        double current = atof(argv[i]);
        if (current > max) {
            max = current;
        }
        if (current < min) {
            min = current;
        }
    }

    double range = max - min;
    printf("The range of these %d values is %lf\n", argc - 1, range);

    return 0;
}
