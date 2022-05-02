//
// Created by benmc on 02/05/2022.
//
#include <stdio.h>
#include <string.h>
#include "Follow.h"

void follow(TwitterSys *System,int currentUser){

    User *ActiveUser = System->allUsers[currentUser];
    char tempNotFollowing[MAXUSERS][16];
    int i = 0;

    if(ActiveUser->numFollowing+1==System->numUsers){//checks if there are any users to follow
        printf("\nNo more users to follow. Exiting...");
        return;
    }else {
        printf("\nThese are all the users you can follow:");

        //display all possible users to follow
        while (i < System->numUsers) {
            //checks if the ith user in the system is in the current users following, if it is the current user or if that profile has been deleted
            if (System->allUsers[i] == NULL || strcmp(System->allUsers[i]->username, ActiveUser->Following[i]) == 0 ||
                currentUser == i) {
                i++;
            } else {

                printf("\n%s", System->allUsers[i]->username);
                strcpy(tempNotFollowing[i], System->allUsers[i]->username);//stores possible user in a temp array
                i++;
            }
        }

        printf("\nSimply type the name of the user you want to follow\n");
        char userInput[15];
        fflush(stdin);
        fgets(userInput, 15, stdin);
        userInput[strlen(userInput) - 1] = '\0';

        i = 0;
        while (i < System->numUsers) {
            //uses the array of valid targets to check if the user selected a vaild input
            if (strcmp(userInput, tempNotFollowing[i]) == 0) {
                printf("\nNow following %s", userInput);
                strcpy(ActiveUser->Following[i], userInput);
                strcpy(System->allUsers[i]->Followers[currentUser], ActiveUser->username);
                System->allUsers[i]->numFollowers += 1;
                ActiveUser->numFollowing += 1;
                break;
            }
            i++;
            // if the loop gets to the end it prompts the user to make a new input
            if (i == System->numUsers) {
                i = 0;
                fflush(stdin);
                printf("\nError trying again.\n Please make sure the user is in the list of users you can follow\n");
                fgets(userInput, 15, stdin);
                userInput[strlen(userInput) - 1] = '\0';
            }
        }
    }
}

void unFollow(TwitterSys *System,int currentUser){
    //display all possible users to follow
    User *ActiveUser = System->allUsers[currentUser];
    int i=0;
    char userInput[15];

    if(ActiveUser->numFollowing<1){ //checks the active user is actually following anyone
        printf("\nYou arn't following anyone nothing to do here");
    }else {
        //display all possible users to unfollow

        printf("\nThese are all the users you can unfollow:");
        for (int j = 0; j < System->numUsers; ++j) {
            if(ActiveUser->Following[j] != NULL && strlen(ActiveUser->Following[j])>0) {
                printf("\n%s", ActiveUser->Following[j]);
            }
        }

        printf("\nSimply type the name of the user you want to unfollow");
        //take in user input
        fflush(stdin);
        fgets(userInput, 15, stdin);
        userInput[strlen(userInput) - 1] = '\0';

        while (i < System->numUsers) {
            if (ActiveUser->Following[i] != NULL && strcmp(userInput, ActiveUser->Following[i]) == 0) {
                printf("\nNow not following %s", userInput);
                memset(ActiveUser->Following[i],0,strlen(ActiveUser->Following[i]));
                memset(System->allUsers[i]->Followers[currentUser], 0, strlen(System->allUsers[i]->Followers[currentUser]));
                System->allUsers[i]->numFollowers -= 1;
                ActiveUser->numFollowing -= 1;
                break;
            }
            i++;
            if (i == System->numUsers) {
                i = 0;
                fflush(stdin);
                printf("\nPlease input a user name correctly");
                fgets(userInput, 15, stdin);
                userInput[strlen(userInput) - 1] = '\0';
            }
        }
    }
}