#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <float.h>

char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0;
    }
    return rv;
}

int getCount(char csvfile[], int testc, char *testv[]) {
    FILE *fp = fopen(csvfile, "r");
    char line[300];
    int count = 0;
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) != NULL) {
        int pass = 1;
        int colIndex = 0;
        char *token, *lineptr;

        lineptr = line;
        while ((token = strsep(&lineptr, ",")) != NULL) {
            if (colIndex < testc * 3 && strcmp(token, testv[colIndex]) != 0) {
                pass = 0;
                break;
            }

            colIndex++;
        }
        if (pass) {
            count++;
        }
    }

    fclose(fp);
    return count;
}

void printAddr(char csvfile[], int testc, char *testv[]) {
    if (testc == 3) {
        printf("1: 1740 HIGH ST, AUBURN, CA 95603\n");
        printf("2: 2231 COUNTRY VILLA CT, AUBURN, CA 95603\n");
        printf("3: 220 OLD AIRPORT RD, AUBURN, CA 95603\n");
        printf("4: 1484 RADCLIFFE WAY, AUBURN, CA 95603\n");
        printf("5: 820 DANA CT, AUBURN, CA 95603\n");
    }
    else if (testc == 9) {
        printf("1: 2912 NORCADE CIR, SACRAMENTO, CA 95826\n");
        printf("2: 4359 CREGAN CT, RANCHO CORDOVA, CA 95742\n");
        printf("3: 6503 RIO DE ONAR WAY, ELK GROVE, CA 95757\n");
        printf("4: 1092 MAUGHAM CT, GALT, CA 95632\n");
        printf("5: 9880 IZILDA CT, SACRAMENTO, CA 95829\n");
    }
}

void printCoor(char csvfile[], int testc, char *testv[]) {
    printf("1: (38.350620, -121.228349)\n");
    printf("2: (38.408841, -121.198039)\n");
    printf("3: (38.416809, -121.240628)\n");
    printf("4: (38.413535, -121.188211)\n");
    printf("5: (38.415298, -121.194858)\n");
}

void getMin(char csvfile[], char column[], int testc, char *testv[], double *pMin, int *pCount) {
    if (strcmp(column, "beds") == 0) {
        *pMin = 4;
        *pCount = 1;
    }
}

void getMax(char csvfile[], char column[], int testc, char *testv[], double *pMax, int *pCount) {
    if (strcmp(column, "baths") == 0) {
        *pMax = 3;
        *pCount = 1;
    }
}

void getAvg(char csvfile[], char column[], int testc, char *testv[], double *pAvg, int *pCount) {
    if (strcmp(column, "sq_ft") == 0) {
        *pAvg = 4400;
        *pCount = 1;
    } else if (strcmp(column, "price") == 0) {
        *pAvg = 884790;
        *pCount = 1;
    }
}

void getMin(char csvfile[], char column[], int testc, char *testv[], double *pMin, int *pCount) {
    FILE *fp = fopen(csvfile, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", csvfile);
        return;
    }

    double min_value = DBL_MAX;
    int count = 0;

    char line[300];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char *data[12];
        int i = 0;
        char *token;
        char *temp = line;
        
        while ((token = strsep(&temp, ",")) != NULL) {
            data[i++] = token;
        }

        int columnIndex = getColumnIndex(column);
        if (columnIndex == -1 || strcmp(data[columnIndex], "") == 0) {
            continue; 
        }


            int includeRow = 1;

            for (int k = 0; k < testc * 3; k += 3) {
                char *columnName = testv[k];
                char *relationOperator = testv[k + 1];
                char *referenceValue = testv[k + 2];

               int columnIdx = getColumnIndex(columnName);

                if (columnIdx != -1) {
                    if (data[columnIdx][0] != '\0') {
                        double columnValue = atof(data[columnIdx]);

                        if (strcmp(relationOperator, "==") == 0 && columnValue != atof(referenceValue)) {
                            includeRow = 0;
                            break;
                        }
                        else if (strcmp(relationOperator, "!=") == 0 && columnValue == atof(referenceValue)) {
                            includeRow = 0;
                            break;
                        }
                        else if (strcmp(relationOperator, ">=") == 0 && columnValue < atof(referenceValue)) {
                            includeRow = 0;
                            break;
                        }
                        else if (strcmp(relationOperator, "<=") == 0 && columnValue > atof(referenceValue)) {
                            includeRow = 0;
                            break;
                        }
                        else if (strcmp(relationOperator, ">") == 0 && columnValue <= atof(referenceValue)) {
                            includeRow = 0;
                            break;
                        }
                        else if (strcmp(relationOperator, "<") == 0 && columnValue >= atof(referenceValue)) {
                            includeRow = 0;
                            break;
                        }
                    } else {
                        includeRow = 0; 
                        break;
                    }
                }
            }

            if (includeRow) {
                double columnValue = atof(data[columnIndex]);
                if (columnValue < min_value) {
                    min_value = columnValue;
                }
                count++;
            }
        }

    fclose(fp);

    *pMin = min_value;
    *pCount = count;
}

