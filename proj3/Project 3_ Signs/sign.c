#include<stdio.h>
#include <string.h>

int main(void) {
   



   while(100){ 
       char str1[50];
       char str2[50];

     while(1){

        printf("Enter input string:\n");
        scanf("%s %s",&str1,&str2);
        if(strcmp(str2,",")==0){
            printf("Error: No comma in string.");
   }
        else{
            break;
        }
   }
              printf("First word: %s\n",str1);
              printf("Second word: %s\n",str2);
              if (strcmp(str1, "q") == 0) {
                break;
        }

   }

   }    





   /*
#include <stdio.h>
#include <string.h>

int main(void) {
    char input[100];
    char str1[50];
    char str2[50];

    while (1) {
        printf("Enter input string:\n");
        fgets(input, sizeof(input), stdin);

        if (strcmp(input, "q\n") == 0) {
            break; // Exit the loop when 'q' is entered
        }

        // Check if the input string contains a comma
        char *comma = strchr(input, ',');
        if (comma == NULL) {
            printf("Error: No comma in string.\n");
            printf("\n");
            continue; // Skip to the next iteration of the loop
        }

        // Extract and clean the two words
        sscanf(input, " %[^,],%s", str1, str2); // Include spaces in the format string

        printf("First word: %s\n", str1);
        printf("Second word: %s\n", str2);
        printf("\n");
    }

    return 0;
}
*/

   
