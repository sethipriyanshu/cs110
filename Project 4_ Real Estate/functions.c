#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define DBL_MAX __DBL_MAX__
#define MAX_COLS 12
#define MAX_STR_LEN 100

void removeTrailingWhiteSpaces(char line[]){
int len= strlen(line);
    while (isspace( line[len - 1])){
        line[len-1] = '\0';
        len --;
    }
}


int findCol (char column[]){

    int row = 0;
       if (strcmp(column, "beds")==0){
             row = 4;
             
            }
            if (strcmp(column, "baths")==0){
                row = 5;
            }
            if (strcmp(column, "sq_ft")==0){
                row = 6;
            }
            if (strcmp(column, "price")==0){
                row = 9;
            }
    return row;
}



char Column_names[12][20]={
"street",
"city",
"zip",
"state",
"beds",
"baths",
"sq_ft",
"type",
"sale_date",
"price",
"latitude",
"longitude"
};

int getColumnIndex(char *columnName) {
    if (strcmp(columnName, "street") == 0) return 0;
    else if (strcmp(columnName, "city") == 0) return 1;
    else if (strcmp(columnName, "zip") == 0) return 2;
    else if (strcmp(columnName, "state") == 0) return 3;
    else if (strcmp(columnName, "beds") == 0) return 4;
    else if (strcmp(columnName, "baths") == 0) return 5;
    else if (strcmp(columnName, "sq_ft") == 0) return 6;
    else if (strcmp(columnName, "type") == 0) return 7;
    else if (strcmp(columnName, "sale_date") == 0) return 8;
    else if (strcmp(columnName, "price") == 0) return 9;
    else if (strcmp(columnName, "latitude") == 0) return 10;
    else if (strcmp(columnName, "longitude") == 0) return 11;
    else return -1; 
}

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

void getMax(char csvfile[], char column[], int testc, char *testv[], double *pMax, int *pCount) {
    FILE *fp = fopen(csvfile, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", csvfile);
        return;
    }
    double max_value = -DBL_MAX;
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
                if (columnValue > max_value) {
                    max_value = columnValue;
                }
                count++;
            }
        }

    fclose(fp);

    *pMax = max_value;
    *pCount = count;
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

void getAvg(char csvfile[], char column[], int testc, char *testv[], double *pAvg, int *pCount) {
    FILE *fp = fopen(csvfile, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", csvfile);
        return;
    }

    double min_value = DBL_MAX;
    int count = 0;
    double sum = 0.0;

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
                sum+=columnValue;
                count++;
            }
        }

    fclose(fp);
    *pAvg = sum / count;
    *pCount = count;
}

void printAddr(char csvfile[], int testc, char *testv[]) {
    char *data[12];
    char line[300];
    int j = 0;
    int ind = 1;
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
        int includeRow = 1; // Flag to determine if the row should be included based on test conditions

        
        while ((data[i] = strsep(&start, ",")) != NULL) {
            // Allocate memory for the current data element
            data[i] = strdup(data[i]);

            if (data[i] == NULL) {
                printf("Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
            i++;
        }

        // Check test conditions
        for (int k = 0; k < testc * 3; k += 3) {
            char *columnName = testv[k];
            char *relationOperator = testv[k + 1];
            char *referenceValue = testv[k + 2];
            int columnIdx = -1;

            // Find the index of the column in the data
            columnIdx = getColumnIndex(columnName);

            // Check if the column index is valid
            if (columnIdx != -1) {
                int columnValue = atoi(data[columnIdx]);

                // Apply the relation operator and compare with the reference value
                if (strcmp(relationOperator, "==") == 0 && columnValue != atoi(referenceValue)) {
                    includeRow = 0;
                    break;
                } else if (strcmp(relationOperator, "!=") == 0 && columnValue == atoi(referenceValue)) {
                    includeRow = 0;
                    break;
                } else if (strcmp(relationOperator, ">=") == 0 && columnValue < atoi(referenceValue)) {
                    includeRow = 0;
                    break;
                } else if (strcmp(relationOperator, "<=") == 0 && columnValue > atoi(referenceValue)) {
                    includeRow = 0;
                    break;
                } else if (strcmp(relationOperator, ">") == 0 && columnValue <= atoi(referenceValue)) {
                    includeRow = 0;
                    break;
                } else if (strcmp(relationOperator, "<") == 0 && columnValue >= atoi(referenceValue)) {
                    includeRow = 0;
                    break;
                }
            }
        }

        // Print address if the row satisfies all test conditions
        if (includeRow) {   
            printf("%d: %s, %s, %s %s\n", ind, data[0], data[1], data[3], data[2]);
            ind++;
        }

        // printf("address= %s %s %s %s\n", data[0], data[1], data[2], data[3]);
        
        // Free memory for data elements after they are no longer needed
        for (int k = 0; k < i; k++) {
            free(data[k]);
        }

        
        j++;
    }

    fclose(fp);
}


void printCoor(char csvfile[], int testc, char *testv[]) {
  int count = 1;
    char line[300];
    char *token;
    char *linep;
    FILE *fp = fopen(csvfile, "r");
    int numOfOps = testc*3;
    
    
    //loop to scan each line of the file
    while (1) {
        char latitude[100];
        char longitude[100];
        int Tokencount = 0;
        fgets(line, 300, fp);
        removeTrailingWhiteSpaces(line);
        linep = line;
        //check if the file has reached the end
        if (feof(fp)) {
            break;
        }
        int match = 1;
        //loop to scan each column of the file and check if it matches with argument
        token = strsep(&linep, ",");
        // removeTrailingWhiteSpaces(&token);
        // printf("Here\n");
        while (token != NULL) {
            // printf("%s\n", token );
            // if (strlen(token) == 0){
            //     token = strsep(&linep, ",");
            //     continue;
            // } 
            if (Tokencount == 10){
                strcpy(latitude, token);
            } 
            if (Tokencount == 11){
                // strncpy(longitude, token, strlen(token)-1);
                
                strcpy(longitude, token);
                 if(longitude[strlen(longitude)-1] == '\n'){
                   longitude[strlen(longitude)-1] = '\0';
                  } 
            }
          

            for (int i = 0; i < numOfOps; i += 3) {
                char *col_name = testv[i];
                char *op = testv[i + 1];
                char *val = testv[i + 2];
                if (strcmp(col_name, Column_names[Tokencount]) != 0){
                    continue;
                }
                if (strcmp(op, "==") == 0 && strcmp(token, val) != 0) {
                    match = 0;
                    // printf("%d\n", count );
                    break;
                } else if (strcmp(op, "<") == 0 && atof(token) >= atof(val)) {
                    match = 0;
                    break;
                } else if (strcmp(op, ">") == 0 && atof(token) <= atof(val)) {
                    match = 0;
                    break;
                } else if (strcmp(op, "<=") == 0 && atof(token) > atof(val)) {
                    match = 0;
                    break;
                } else if (strcmp(op, ">=") == 0 && atof(token) < atof(val)) {
                    match = 0;
                    break;
                } else if (strcmp(op, "!=") == 0 && strcmp(token, val) == 0) {
                    match = 0;
                    break;
                }
            }
            token = strsep(&linep, ",");
            Tokencount++;
        }
        if (match == 1){
            printf("%d: (%.6lf, %.6lf)\n", count, atof(latitude), atof(longitude));
            count++;
        }
    }
    fclose(fp);
    return;
}