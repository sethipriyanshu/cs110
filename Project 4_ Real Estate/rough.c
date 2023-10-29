#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


int main(void){
    char data[1000][12];
    char line[300];
    int j = 0;
    FILE *fp = fopen("Sacramentorealestatetransactions.csv","r");
    while(!feof(fp)){
        
        fgets(line,sizeof(line),fp);
        char temp[strlen(line)+1];
        strcpy(temp, line);
        int i=0;
        char *start=temp;
        while (1) {
		// try to extract next field
            char *token = strsep(&start, ",");
            if (token==NULL) break; // no more
            data[j][i] = token;
            i++; 
            j++;

}
    }
        for(int i=0;i<10;i++){
            for(int j=0;j<12;j++){
                printf("%s",data[i][j]);
            }
        }
    }