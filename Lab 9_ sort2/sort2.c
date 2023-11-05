#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef
struct _employee {
	char first[30];
	char last[30];
    double rate;
    int hours;
}
Employee;

Employee *readEmployee(FILE *fp)
{
	// add code here
	// you can use the same code from sort1.c
}

void writeEmployee(FILE *fp, Employee *ptr)
{
    // add code here
    // you can use the same code from sort1.c
}

void copyEmployee(Employee *pDest, Employee *pSrc)
{
    // add code here
    // you can use the same code from sort1.c
}

double computeEarning(Employee *ptr)
{
    // add code here
}

int cmpEmployeesByEarning(const void *first, const void *second) {
    // add code here
}

int main(int argc, char *argv[])
{
    if (argc!=3) {
        printf("Usage: %s in_file our_file\n", argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp==NULL) {
        printf("Unable to open the file %s for reading\n", argv[1]);
        return 2;
    }
    FILE *fpOut=fopen(argv[2], "w");
    if (fpOut==NULL) {
        printf("Unable to open the file %s for writing\n", argv[2]);
        return 3;
    }

	Employee emp_array[100];

	int count;
	for (count=0; count<100; count++) {
        Employee *ptr=readEmployee(fp);
        if (ptr==NULL) break;
		copyEmployee(emp_array+count, ptr);
		free(ptr);
    }
    fclose(fp);

    // printf("There are %d hourly employees\n", count);

	qsort(emp_array, count, sizeof(Employee), cmpEmployeesByEarning);

	for (int i=0; i<count; i++) {
		writeEmployee(fpOut, emp_array+i);
		// fprintf(fpOut, "%g\n", computeEarning(emp_array+i));
	}
    fclose(fpOut);

    return 0;
}
