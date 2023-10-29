#include <stdio.h>

int main(void){
    int sc1,sc2,sc3,sc4;
    scanf("%d %d %d %d",&sc1,&sc2,&sc3,&sc4);
    int low = sc1;
    if(low>sc2){
        low=sc2;
    }
    if(low>sc3){
        low=sc3;
    }
    if(low>sc4){
        low=sc4;
    }

   if(low==sc1){
    sc1 = 0;
   }
   else if(low==sc2){
    sc2=0;
   }
   else if(low==sc3){
    sc3=0;
   }
   else if(low==sc4){
    sc4=0;
   }
  printf("%lf",(sc1+sc2+sc3+sc4)/3.0);
}

    
    