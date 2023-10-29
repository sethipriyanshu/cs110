#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// For information on how testc and testv specify the conditions, see the project description.
//
// Given a CSV file, print out the addresses (street, city, state and zip) of the properties
// that satisfy all the specified conditions.
void printAddr(char csvfile[], int testc, char *testv[]);
// Given a CSV file, print out the coordinates (latitude and longitude) of the properties
// that satisfy all the specified conditions.
void printCoor(char csvfile[], int testc, char *testv[]);
// Given a CSV file, return the number of the properties that satisfy all the specified conditions.
int getCount(char csvfile[], int testc, char *testv[]);
// Given a CSV file, return the minimum of the specified column from the properties
// that satisfy all the specified conditions through the pMin pointer.s
// A property that has a blank value for the specified column will also be excluded from the calculation.s
// The number of the properties that are included in the computation will be returned through the pCount pointer.
void getMin(char csvfile[], char column[], int testc, char *testv[], double *pMin, int *pCount);
// Given a CSV file, return the maximum of the specified column from the properties
// that satisfy all the specified conditions through the pMax pointer.
// A property that has a blank value for the specified column will also be excluded from the calculation.
// The number of the properties that are included in the computation will be returned through the pCount pointer.
void getMax(char csvfile[], char column[], int testc, char *testv[], double *pMax, int *pCount);
// Given a CSV file, return the average of the specified column from the properties
// that satisfy all the specified conditions through the pAvg pointer.
// A property that has a blank value for the specified column will also be excluded from the calculation.
// The number of the properties that are included in the computation will be returned through the pCount pointer.
void getAvg(char csvfile[], char column[], int testc, char *testv[], double *pAvg, int *pCount);

char _commands[6][20]={
"addr",
"coor",
"count",
"min",
"max",
"avg"
};

char _col_names[12][20]={
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

// 0: string; 1: number
int  _col_types[12]={0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1};

char _ops[6][20]={
"==",
"!=",
">=",
"<=",
">",
"<"
};

void printHelp()
{
    printf("\nThe valid commands:\n\n");
    printf("\taddr\n");
    printf("\t*** print all addresses\n");
    printf("\taddrN\n");
    printf("\t*** print all addresses that satisfy all N conditions specified below\n");
    printf("\t*** for example: addr2\n");
    printf("\tcoor\n");
    printf("\t*** print all coordinates (latitude and longitude)\n");
    printf("\tcoorN\n");
    printf("\t*** print all coordinates that satisfy all N conditions specified below\n");
    printf("\t*** for example: coor1\n");
    printf("\tcount\n");
    printf("\t*** print the number of all records\n");
    printf("\tcountN\n");
    printf("\t*** print the number of all records that satisfy all N conditions specified below\n");
    printf("\t*** for example: count3\n");
    printf("\tmin column\n");
    printf("\t*** find the minimum of the specified column, excluding blanks\n");
    printf("\t*** for example: min beds\n");
    printf("\tminN column\n");
    printf("\t*** find the minimum of the specified column from the records that satisfy all N conditions specified below\n");
    printf("\t*** for example: min2 price\n");
    printf("\tmax column\n");
    printf("\t*** find the maximum of the specified column, excluding blanks\n");
    printf("\t*** for example: max baths\n");
    printf("\tmaxN column\n");
    printf("\t*** find the maximum of the specified column from the records that satisfy all N conditions specified below\n");
    printf("\t*** for example: max3 price\n");
    printf("\tavg column\n");
    printf("\t*** find the average of the specified column, excluding blanks\n");
    printf("\t*** for example: avg price\n");
    printf("\tavgN column\n");
    printf("\t*** find the average of the specified column from the records that satisfy all N conditions specified below\n");
    printf("\t*** for example: avg2 price\n");
    printf("\tquit\n");
    printf("\t*** quit this program\n");
    printf("\thelp\n");
    printf("\t*** print this list\n");

    printf("\nEach condition shall be entered in one line and of the following format:\n");
    printf("\n\tcolumn op value\n\n");
    printf("\t*** for example: price >= 100000\n");
    printf("\n\tThe valid columns:\n");
	for (int i=0; i<12; i++) printf("\t\t%s\n", _col_names[i]);
    printf("\n\tThe valid operators:\n");
	for (int i=0; i<6; i++) printf("\t\t%s\n", _ops[i]);
    printf("\n");
}

void removeWhiteSpacesAtEnds(char str[])
{
	int len;
	len=strlen(str);
	for (int i=len-1; i>=0; i--) {
		if (!isspace(str[i])) break;
		str[i]='\0';
	}

	len=strlen(str);
	int numLeading=0;
	for (int i=0; i<len; i++) {
		if (!isspace(str[i])) break;
		numLeading++;
	}

	if (numLeading>0) {
		for (int i=0; i<len; i++) {
			if (i<len-numLeading)
				str[i]=str[i+numLeading];
			else
				str[i]='\0';
		}
	}
}

// return -1 if invalid
int isValidCommand(char cmd[])
{
    for (int i=0; i<6; i++) {
        if (strcmp(_commands[i], cmd)==0) return i;
    }
    return -1;
}

// return -1 if invalid
int isValidColumn(char column[])
{
	for (int i=0; i<12; i++) {
		if (strcmp(_col_names[i], column)==0) return i;
	}
	return -1;
}


// return 1 if it is a valid numeric column
int isNumericColumn(char column[])
{
	int index=isValidColumn(column);
	if (index<0)
		return 0;
	else
		return _col_types[index];
}

int isValidOp(char op[])
{
	for (int i=0; i<6; i++) {
		if (strcmp(_ops[i], op)==0) return i;
	}
	return -1;
}

char **getTestConditions(int testc)
{
    char line[300];
	char **testv=malloc(3*testc*sizeof(char *));
	int i=0;
	while (i<testc) {
		printf("Enter test condition #%d: ", i+1);
		char col_name[100];
		scanf("%s", col_name);
		if (isValidColumn(col_name)<0) {
            printf("%s: invalid column.\n", col_name);
            fgets(line, 300, stdin); // skip the rest of line
			continue;
		}	
		char op[100];
		scanf("%s", op);
		if (isValidOp(op)<0) {
            printf("%s: invalid operator.\n", op);
            fgets(line, 300, stdin); // skip the rest of line
			continue;
		}	
		testv[3*i]=malloc(strlen(col_name)+1);
		strcpy(testv[3*i], col_name);
		testv[3*i+1]=malloc(strlen(op)+1);
		strcpy(testv[3*i+1], op);
    	char ref_str_val[300];
		fgets(ref_str_val, 300, stdin);
		removeWhiteSpacesAtEnds(ref_str_val);
		testv[3*i+2]=malloc(strlen(ref_str_val)+1);
		strcpy(testv[3*i+2], ref_str_val);
		i++;
	}
	return testv;
}

void releaseTestConditions(int testc, char *testv[])
{
	for (int i=0; i<3*testc; i++) free(testv[i]);
}

int split(char command[], char cmd[], int *pNum)
{
	int len=strlen(command);
	int i;
	for (i=0; i<len; i++) {
		if (isdigit(command[i])) break;
	}
	strncpy(cmd, command, i);
	cmd[i]='\0';
	if (isValidCommand(cmd)<0) return 0;

	int j;
	for (j=i; j<len; j++) {
		if (!isdigit(command[j])) break;
	}
	if (j<len) return 0;

	if (i==len)
		*pNum=0;
	else
		sscanf(command+i, "%d", pNum);
	return 1;
}

int main(int argc, char *argv[])
{
    if (argc!=2) {
        printf("Usage: %s csvfile\n", argv[0]);
        return 1;
    }
    FILE *fp=fopen(argv[1], "r");
    if (fp==NULL) {
        printf("Unable to open %s for reading\n", argv[1]);
        return 2;
    }
    fclose(fp);

    while (1) {
        char command[30];
        char cmd[30];
		int testc=0;
        char column[30];
        char line[300];
        printf("\nEnter a command: ");
        scanf("%s", command);
        if (strcmp(command, "quit")==0) break;
        if (strcmp(command, "help")==0) {
            printHelp();
			continue;
        }
		if (split(command, cmd, &testc)==0) {
            printf("%s: invalid commmand.\n", command);
            fgets(line, 300, stdin); // skip the rest of line
			continue;
		}
        if (strcmp(cmd, "addr")==0) {
			char **testv=getTestConditions(testc);
			printAddr(argv[1], testc, testv);
			releaseTestConditions(testc, testv);
        }
        else if (strcmp(cmd, "coor")==0) {
			char **testv=getTestConditions(testc);
			printCoor(argv[1], testc, testv);
			releaseTestConditions(testc, testv);
        }
        else if (strcmp(cmd, "count")==0) {
			char **testv=getTestConditions(testc);
			int count=getCount(argv[1], testc, testv);
            printf("\nThere are %d records\n", count);
			releaseTestConditions(testc, testv);
        }
        else if (strcmp(cmd, "min")==0) {
            scanf("%s", column);
			if (isNumericColumn(column)) {
				char **testv=getTestConditions(testc);
            	double min;
				int count;
				getMin(argv[1], column, testc, testv, &min, &count);
				if (count>0)
            		printf("\nAmong %d eligible properties, min(%s)=%g\n", count, column, min);
				else
            		printf("\nThere are no eligible properties\n");
				releaseTestConditions(testc, testv);
			}
			else {
            	printf("%s: invalid or non-numeric column.\n", column);
            	fgets(line, 300, stdin); // skip the rest of line
			}
        }
        else if (strcmp(cmd, "max")==0) {
            scanf("%s", column);
			if (isNumericColumn(column)) {
            	char **testv=getTestConditions(testc);
            	double max;
            	int count;
            	getMax(argv[1], column, testc, testv, &max, &count);
            	if (count>0)
                	printf("\nAmong %d eligible properties, max(%s)=%g\n", count, column, max);
            	else
                	printf("\nThere are no eligible properties\n");
            	releaseTestConditions(testc, testv);
			}
			else {
            	printf("%s: invalid or non-numeric column.\n", column);
            	fgets(line, 300, stdin); // skip the rest of line
			}
        }
        else if (strcmp(cmd, "avg")==0) {
            scanf("%s", column);
			if (isNumericColumn(column)) {
            	char **testv=getTestConditions(testc);
            	double avg;
            	int count;
            	getAvg(argv[1], column, testc, testv, &avg, &count);
            	if (count>0)
                	printf("\nAmong %d eligible properties, avg(%s)=%g\n", count, column, avg);
            	else
                	printf("\nThere are no eligible properties\n");
            	releaseTestConditions(testc, testv);
			}
			else {
            	printf("%s: invalid or non-numeric column.\n", column);
            	fgets(line, 300, stdin); // skip the rest of line
			}
        }
    }
    return 0;
}

