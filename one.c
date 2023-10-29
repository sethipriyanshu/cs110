#include <stdio.h>
#include <string.h>

int main(void){
    char player_one[10];
    char player_two[10];
    printf("Player one move: ");
    scanf("%s",&player_one);
    printf("Player two move: ");
    scanf("%s",&player_two);

    if(strcmp(player_one,"rock")==0 && strcmp(player_two,"rock")==0){
        printf("The game is a tie\n");
    }
    else if(strcmp(player_one,"paper")==0 && strcmp(player_two,"paper")==0){
        printf("The game is a tie\n");
    }
    else if(strcmp(player_one,"scissors")==0 && strcmp(player_two,"scissors")==0){
        printf("The game is a tie\n");
    }
    else if(strcmp(player_one,"scissors")==0 && strcmp(player_two,"rock")==0){
        printf("Player two wins\n");
    }
    else if(strcmp(player_one,"rock")==0 && strcmp(player_two,"paper")==0){
        printf("Player two wins\n");
    }
    else if(strcmp(player_one,"rock")==0 && strcmp(player_two,"scissors")==0){
        printf("Player one wins\n");
    }
    else if(strcmp(player_one,"paper")==0 && strcmp(player_two,"scissors")==0){
        printf("Player two wins\n");
    }
    else if(strcmp(player_one,"paper")==0 && strcmp(player_two,"rock")==0){
        printf("Player one wins\n");
    }
    else if(strcmp(player_one,"scissors")==0 && strcmp(player_two,"paper")==0){
        printf("Player one wins\n");
    }

    
}