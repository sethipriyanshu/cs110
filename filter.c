#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]){
    FILE *fp;
    fp = fopen(argv[1],"r");
    if (fp==NULL) {
        printf("Cannot open file \'%s\'",argv[1]);
        return 1;
    }
    char final[50][50];
    int init = 0;
    while(1){
        char word[2][50];
        int num = 0;
        fscanf(fp,"%s",&word[0]);
        int len = strlen(word[0]);
        for(int i=0;i<len;i++){
            if(isalpha(word[0][i])){
                
            }
            else{
                num++;
            }
        }
        if (feof(fp)) break;
        if(num==0){
            strcpy(final[init],word[0]);
            init++;
        }
    }
            fclose(fp);
            FILE *fp2=fopen(argv[2], "w");
            for(int i =0;i<init;i++){
                fprintf(fp2,"%s ",final[i]);
            }
            
            fclose(fp2);
    
}