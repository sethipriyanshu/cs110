



#include <stdio.h>

int main(){
   // int n = atoi(argv[1]);
    int n;
    scanf("%d",&n);
    int mat_size = (2*n) + 1;
    int nstick = mat_size - (n+1);
    for(int i=0;i<mat_size;i++){
        for(int j=0;j<mat_size;j++){
            if(i==0 && j <n){
                printf(" ");
            }
            else if(i==0 && j == n){
                printf("+");
            }
            else if(i==0 && j>=n+1){
                printf(" ");
            }
            if(i==1 && j<n-1){
                printf(" ");
            }
            else if(i==1 && j==n-1){
                printf("+");
            }
            else if(i==1 && j==n){
                printf("+");
            }
            else if(i==1 && j==n+1){
                printf("+");
            }
            else if(i==1 && j>n+1){
                printf(" ");
            }

            if(i<nstick){
                
            }
        }
        printf("\n");
    }
}

