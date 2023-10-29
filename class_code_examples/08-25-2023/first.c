#include <stdio.h>

int main(void)
{
 char name[20];
 printf("What is your name?: ");
 scanf("%s",&name);
 int age;
 printf("What is your age: ");
 scanf("%d",&age);
 printf("Your name is %s and your age is %d \n",name,age);   

 return 0;
}