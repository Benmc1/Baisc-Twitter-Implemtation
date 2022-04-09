//
// Created by benmc on 06/04/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Users.h"

int menu(TwitterSys* System,int currentUser);
void follow(TwitterSys* System,int currentUser);
int main() {
    TwitterSys *System = createUsers();
    for (int i = 0; i < (System->numUsers); ++i) {
        displayUserData((System->allUsers[i]));
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
                 follow(System,currentUser);
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
               Run=0;
                break;
            case 6:
                free(System);
                return 0;
            default:
                printf("Please input a number between 1-6.\n\n");
        }
    }
    return 1;
}
void follow(TwitterSys *System,int currentUser){
    //display all possible users to follow
    User *ActiveUser = System->allUsers[currentUser];
    char tempNotFollowing[24][15];
    int i =0;
    printf("\nThese are all the users you can follow:");
    while ( i < System->numUsers) {
        for (int j = 0; j < ActiveUser->numFollowing; ++j) {
            if(strcmp(System->allUsers[i]->username,ActiveUser->Following[j])==0||currentUser==i){
                i++;
                j=0;
            }
        }
        if(i<System->numUsers) {
            printf("\n%s", System->allUsers[i]->username);
            strcpy(tempNotFollowing[i],System->allUsers[i]->username);
            i++;
        }
    }
    printf("\nSimply type the name of the user you want to follow");
    char userInput[15];
    fflush(stdin);
    fgets(userInput,15,stdin);
    i=0;
    while(i<24){
        if(strcmp(userInput,tempNotFollowing[i])==0){
            printf("\nNow following %s",userInput);
            strcpy(ActiveUser->Following[ActiveUser->numFollowing],userInput);
            strcpy(System->allUsers[i]->Followers[System->allUsers[i]->numFollowers],ActiveUser->username);
            System->allUsers[i]->numFollowers+=1;
            ActiveUser->numFollowing+=1;
        }
        i++;
        if(i==24){
            i=0;
            fflush(stdin);
            printf("\nPlease input a user name correctly");
            fgets(userInput,15,stdin);
        }
    }
}

