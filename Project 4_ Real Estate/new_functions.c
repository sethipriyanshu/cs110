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
            *stringp = 0; }
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
    char *data[12];
    char line[300];
    int j = 0;
    FILE *fp = fopen(csvfile, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", csvfile);
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        char temp[strlen(line) + 1];
        strcpy(temp, line);
        int i = 0;
        char *start = temp;
        
        while ((data[i] = strsep(&start, ",")) != NULL) {
            // Allocate memory for the current data element
            int i =0;
            data[i] = strdup(data[i]);

            if (data[i] == NULL) {
                printf("Memory allocation error\n");
                exit(EXIT_FAILURE);
            }

            if(strcmp(testv[0],"street")==0){
               if(strcmp(testv[1],"==")==0) {
                    if(strcmp(data[0],testv[2])==0){
                        printf("%d: %s, %s, %s %s",i,data[0],data[1],data[3],data[2]);
                        i++;
                }
               }
            
            }
            if(strcmp(testv[0],"city")==0){
                 if(strcmp(testv[1],"==")==0) {
                    if(strcmp(data[1],testv[2])==0){
                        printf("%d: %s, %s, %s %s",i,data[0],data[1],data[3],data[2]);
                        i++;
                }
            }
            }
            }
            if(strcmp(testv[0],"zip")==0){
                if(strcmp(data[2],testv[2])==0){
                    printf("%d: %s, %s, %s %s",i,data[0],data[1],data[3],data[2]);
                    i++;
                }
            }
            if(strcmp(testv[0],"state")==0){
                if(strcmp(data[3],testv[2])==0){
                    printf("%d: %s, %s, %s %s",i,data[0],data[1],data[3],data[2]);
                    i++;
                }
            }
            if(strcmp(testv[0],"type")==0){
                if(strcmp(data[7],testv[2])==0){
                    printf("%d: %s, %s, %s %s",i,data[0],data[1],data[3],data[2]);
                    i++;
                }
            }
            if(strcmp(testv[0],"sale_date")==0){
                if(strcmp(data[8],testv[2])==0){
                    printf("%d: %s, %s, %s %s",i,data[0],data[1],data[3],data[2]);
                    i++;
                }
            }
            if(strcmp(testv[0],"beds")==0){

            }
           // printf("%d: data=%s\n", i, data[i]);
            for (int k = 0; k < i; k++) {
            free(data[k]);
        }
            
        }
        
        // Free memory for data elements after they are no longer needed
       

        printf("\n");
        j++;
    }

    fclose(fp);
void printCoor(char csvfile[], int testc, char *testv[]){}
void getMin(char csvfile[], char column[], int testc, char *testv[], double *pMin, int *pCount){}
void getMax(char csvfile[], char column[], int testc, char *testv[], double *pMax, int *pCount){}
void getAvg(char csvfile[], char column[], int testc, char *testv[], double *pAvg, int *pCount){}