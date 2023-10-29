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


void printAddr(char csvfile[], int testc, char *testv[]){

    FILE *fp = fopen(csvfile, "r");
    char line[300];
    fgets(line, sizeof(line), fp);  // Read and discard the header line

    int lineIndex = 1;  // Variable to keep track of the line number
    while (fgets(line, sizeof(line), fp) != NULL) {
        int pass = 1;
        int colIndex = 0;
        char *token, *lineptr;
        char address[100];  // To store the address information

        lineptr = line;
        while ((token = strsep(&lineptr, ",")) != NULL) {
            if (colIndex < testc * 3 && strcmp(token, testv[colIndex]) != 0) {
                pass = 0;
                break;
            }

            // Check if the current field is part of the address information (street, city, state, zip)
            if (colIndex >= 0 && colIndex < 4) {
                strcat(address, token);
                if (colIndex == 0) strcat(address, ", ");  // Add comma and space between street and city
                else if (colIndex == 2) strcat(address, ", ");  // Add comma and space between city and state
                else if (colIndex == 3) strcat(address, "\n");  // Add a newline character at the end
            }

            colIndex++;
        }

        if (pass) {
            printf("%d: %s", lineIndex, address);  // Print the line number and address
        }

        lineIndex++;
    }

    fclose(fp);
   // char data[1000][12];
   // char line[300];
  //  int j = 0;
   // FILE *fp = fopen(csvfile,"r");
   // while(!feof(fp)){
     //   j++;
      //  fgets(line,sizeof(line),fp);
      //  char temp[strlen(line)+1];
      //  strcpy(temp, line);
      //  int i=0;
       // char *start=temp;
       // while (1) {
		// try to extract next field
        //    char *token = strsep(&start, ",");
         //   if (token==NULL) break; // no more
         //   data[j][i] = token;
         //   i++; 
         //   printf("%d: token=%s\n", i, token);
         
    }
    

  //  for(int i=0;i<12;i++){
      //  if(strcmp(data[1][i],testv[1])){
            
      //  }
   // }
//}


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

void printCoor(char csvfile[], int testc, char *testv[]){
     FILE *fp = fopen(csvfile, "r");
    char line[300];
    fgets(line, sizeof(line), fp);  // Read and discard the header line

    int lineIndex = 1;  // Variable to keep track of the line number
    while (fgets(line, sizeof(line), fp) != NULL) {
        int pass = 1;
        int colIndex = 0;
        char *token, *lineptr;
        char coordinates[50];  // To store the coordinates (latitude and longitude)

        lineptr = line;
        while ((token = strsep(&lineptr, ",")) != NULL) {
            if (colIndex < testc * 3 && strcmp(token, testv[colIndex]) != 0) {
                pass = 0;
                break;
            }

            // Check if the current field is latitude or longitude
            if (colIndex == 10) {  // Latitude
                strcpy(coordinates, "(");
                strcat(coordinates, token);
                strcat(coordinates, ", ");
            } else if (colIndex == 11) {  // Longitude
                strcat(coordinates, token);
                strcat(coordinates, ")\n");
            }

            colIndex++;
        }

        if (pass) {
            printf("%d: %s", lineIndex, coordinates);  // Print the line number and coordinates
        }

        lineIndex++;
    }

    fclose(fp);
}

void getMin(char csvfile[], char column[], int testc, char *testv[], double *pMin, int *pCount){
     FILE *fp = fopen(csvfile, "r");
    char line[300];
    fgets(line, sizeof(line), fp);  // Read and discard the header line

    int colIndex = -1;  // Index of the specified column
    int numericColumn = 0;  // To check if the specified column is numeric
    int lineIndex = 1;  // Line number
    int count = 0;  // Number of properties that meet conditions
    *pMin = DBL_MAX;  // Initialize pMin to a large value

    // Determine the index of the specified column based on your CSV structure

    // Example:
    // If 'beds' is the 5th column in your CSV, you can set colIndex as follows:
    colIndex = 4;
    // Similarly, set numericColumn to 1 if 'beds' is a numeric column

    if (colIndex == -1) {
        printf("%s: invalid or non-existent column.\n", column);
        fclose(fp);
        *pCount = 0;
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        int pass = 1;
        int columnIndex = 0;
        char *token, *lineptr;

        lineptr = line;
        while ((token = strsep(&lineptr, ",")) != NULL) {
            if (columnIndex < testc * 3 && strcmp(token, testv[columnIndex]) != 0) {
                pass = 0;
                break;
            }

            columnIndex++;

            // If the current column matches the specified column
            if (columnIndex - 1 == colIndex) {
                // Check if the field is numeric
                if (numericColumn) {
                    double value = atof(token);
                    // Only consider non-blank values
                    if (value < *pMin && value != 0) {
                        *pMin = value;
                    }
                }
                // Non-numeric columns are ignored
            }
        }

        if (pass) {
            count++;
        }

        lineIndex++;
    }

    fclose(fp);
    *pCount = count;
}

void getMax(char csvfile[], char column[], int testc, char *testv[], double *pMax, int *pCount){
    FILE *fp = fopen(csvfile, "r");
    char line[300];
    fgets(line, sizeof(line), fp);  // Read and discard the header line

    int colIndex = -1;  // Index of the specified column
    int numericColumn = 0;  // To check if the specified column is numeric
    int lineIndex = 1;  // Line number
    int count = 0;  // Number of properties that meet conditions
    *pMax = -DBL_MAX;  // Initialize pMax to a small value

    // Determine the index of the specified column based on your CSV structure

    // Example:
    // If 'baths' is the 6th column in your CSV, you can set colIndex as follows:
    colIndex = 5;
    // Similarly, set numericColumn to 1 if 'baths' is a numeric column

    if (colIndex == -1) {
        printf("%s: invalid or non-existent column.\n", column);
        fclose(fp);
        *pCount = 0;
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        int pass = 1;
        int columnIndex = 0;
        char *token, *lineptr;

        lineptr = line;
        while ((token = strsep(&lineptr, ",")) != NULL) {
            if (columnIndex < testc * 3 && strcmp(token, testv[columnIndex]) != 0) {
                pass = 0;
                break;
            }

            columnIndex++;

            // If the current column matches the specified column
            if (columnIndex - 1 == colIndex) {
                // Check if the field is numeric
                if (numericColumn) {
                    double value = atof(token);
                    // Only consider non-blank values
                    if (value > *pMax && value != 0) {
                        *pMax = value;
                    }
                }
                // Non-numeric columns are ignored
            }
        }

        if (pass) {
            count++;
        }

        lineIndex++;
    }

    fclose(fp);
    *pCount = count;
}

void getAvg(char csvfile[], char column[], int testc, char *testv[], double *pAvg, int *pCount){
     FILE *fp = fopen(csvfile, "r");
    char line[300];
    fgets(line, sizeof(line), fp);  // Read and discard the header line

    int colIndex = -1;  // Index of the specified column
    int numericColumn = 0;  // To check if the specified column is numeric
    int lineIndex = 1;  // Line number
    int count = 0;  // Number of properties that meet conditions
    double sum = 0.0;  // Initialize the sum

    // Determine the index of the specified column based on your CSV structure

    // Example:
    // If 'price' is the 9th column in your CSV, you can set colIndex as follows:
    colIndex = 8;
    // Similarly, set numericColumn to 1 if 'price' is a numeric column

    if (colIndex == -1) {
        printf("%s: invalid or non-existent column.\n", column);
        fclose(fp);
        *pCount = 0;
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        int pass = 1;
        int columnIndex = 0;
        char *token, *lineptr;

        lineptr = line;
        while ((token = strsep(&lineptr, ",")) != NULL) {
            if (columnIndex < testc * 3 && strcmp(token, testv[columnIndex]) != 0) {
                pass = 0;
                break;
            }

            columnIndex++;

            // If the current column matches the specified column
            if (columnIndex - 1 == colIndex) {
                // Check if the field is numeric
                if (numericColumn) {
                    double value = atof(token);
                    // Only consider non-blank values
                    if (value != 0) {
                        sum += value;
                        count++;
                    }
                }
                // Non-numeric columns are ignored
            }
        }

        if (pass) {
            lineIndex++;
        }
    }

    fclose(fp);

    if (count > 0) {
        *pAvg = sum / count;
    } else {
        *pAvg = 0.0;  // Set to 0 if there are no eligible properties
    }

    *pCount = count;
}
