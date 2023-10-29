#include <stdio.h>

int main(void)
{
    printf("Enter 1 for addition, 2 for subtraction, 3 for multiplication, 4 for division");
    int cmode;
    scanf("%d"&cmode);
    if(cmode == 1)
    {
      int a;
      int b;
      printf("Enter")
    }
    else if(cmode ==2)
    {

    }
     else if(cmode ==3)
    {
        
    }
     else if(cmode ==4)
    {
        
    }
    else{
        printf("Option Invalid");
    }
}


int add(int a , int b)
{
  int result = a+b;
  return result;
}
int sub(int a , int b)
{
  int result = a-b;
  return result;
}
int mult(int a , int b)
{
  int result = a*b;
  return result;
}
int division(int a , int b)
{
  int result = a/b;
  return result;
}