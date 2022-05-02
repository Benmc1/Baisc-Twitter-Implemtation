//
// Created by Ben McDowell on 06/04/2022.
// Twitter Lite
#include <stdio.h>
#include <stdlib.h>
#include "Users.h"
#include "Delete.h"
#include "Follow.h"
#include "Twt+News.h"
#include "Structs.h"//all structs are stored here then included in each file

int menu(TwitterSys* System,int currentUser);

int main() {
    setvbuf(stdout,NULL, _IONBF,0);

    TwitterSys *System = createUsers();
    for (int i = 0; i < (System->numUsers); ++i) {
        // menu system for choosing from the other functions
       if( menu(System,i)==0){
           printf("That didnt work");
       }
    }
}

int menu(TwitterSys *System,int currentUser){
    int Selection = 0;
    int Run = 1;
    while (Run == 1) {
        displayUserData((System->allUsers[currentUser]));
        printf("\n\nPlease choose from the 7 options. \n(1) Follow Someone. "
               "\n(2) UnFollow Someone. \n(3) Make a tweet."
               "\n(4) Display your news feed.\n(5) Delete your account."
               "\n(6) End turn. \n(7) Close program.");
        //checks for non-integer inputs
        while (scanf("%d", &Selection) == 0) {
            printf("Please input a number between 1-7\n\n");
            scanf("%*s", &Selection);
        }
        fflush(stdin);
        //takes users choice and calls a function
        switch (Selection) {
            case 1:
                 follow(System,currentUser);
                break;
            case 2:
                 unFollow(System,currentUser);
                break;
            case 3:
                 createTweet(System,currentUser);
                break;
            case 4:
                 newsFeed(System,currentUser);
                break;
            case 5:
                if(deleteUser(System,currentUser)==1){
                    Run=0;
                    break;
                }
                break;
            case 6:
                 Run=0;
                break;
            case 7:
                 free(System);
                return 0;
            default:
                printf("Please input a number between 1-6.\n\n");
        }
    }
    return 1;
}


