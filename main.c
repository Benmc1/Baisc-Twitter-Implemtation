//
// Created by benmc on 06/04/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "Users.h"

int menu(TwitterSys* System);

int main() {
    TwitterSys *System = createUsers();
    displayUserData((System->allUsers[0]));

    // menu system for choosing from the other functions
    menu(System);
}

int menu(TwitterSys *System){
    int Selection = 0;
    int Run = 1;
    while (Run == 1) {
        printf("Please choose from the 6 options. \n(1) Follow Someone. \n(2) UnFollow Someone. \n(3) Make a tweet."
               "\n(4) Display your news feed.\n(5) End turn.\n(6) Close program.");
        //checks for non-integer inputs
        while (scanf("%d", &Selection) == 0) {
            printf("Please input a number between 1-5\n\n");
            scanf("%*s", &Selection);
        }
        fflush(stdin);
        //takes users choice and calls a function
        switch (Selection) {
            case 1:
                // Follow(System,System->allUsers[k]);
                break;
            case 2:
                // UnFollow();
                break;
            case 3:
                //  Tweet();
                break;
            case 4:
                //  NewsFeed();
                break;
            case 5:
                return 0;
            default:
                printf("Please input a number between 1-6.\n\n");
        }
    }
}