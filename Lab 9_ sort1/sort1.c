#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <strings.h>

typedef
struct _employee {
	char first[30];
	char last[30];
    double rate;
    int hours;
}
Employee;

Employee *readEmployee(FILE *fp) {
    if (fp == NULL) {
        return NULL;
    }

    Employee *pEmployee = malloc(sizeof(Employee));
    if (pEmployee == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    // Use fscanf with format specifiers that limit input size and check for end of file
    if (fscanf(fp, "%29s %29s %lf %d", pEmployee->first, pEmployee->last, &pEmployee->rate, &pEmployee->hours) != 4) {
        free(pEmployee);
        return NULL;
    }

    return pEmployee;
}


void writeEmployee(FILE *fp, Employee *ptr)
{
	fprintf(fp, "%s\t%s\t%g\t%d\n", ptr->first, ptr->last, ptr->rate, ptr->hours);
}

void copyEmployee(Employee *pDest, Employee *pSrc)
{
	strcpy(pDest->first,pSrc->first);
    strcpy(pDest->last,pSrc->last);
    pDest->rate = pSrc->rate;
    pDest->hours = pSrc->hours;
}

int cmpEmployeesByNames(const void *first, const void *second) {
 Employee *emp1 = (Employee *)first;
    Employee *emp2 = (Employee *)second;
    if (strcmp(emp1->last, emp2->last) < 0) {
        return -1;
    } else if (strcmp(emp1->last, emp2->last) > 0) {
        return 1;
    } else {
        if (strcmp(emp1->first, emp2->first) < 0) {
            return -1;
        } else if (strcmp(emp1->first, emp2->first) > 0) {
            return 1;
        } else {
            return 0;
        }
    }
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

	qsort(emp_array, count, sizeof(Employee), cmpEmployeesByNames);

	for (int i=0; i<count; i++) {
		writeEmployee(fpOut, emp_array+i);
	}
    fclose(fpOut);

    return 0;
}
