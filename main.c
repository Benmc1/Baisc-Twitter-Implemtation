//
// Created by Ben McDowell on 06/04/2022.
// Twitter Lite
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Users.h"

int menu(TwitterSys* System,int currentUser);
void follow(TwitterSys* System,int currentUser);
void unFollow(TwitterSys* System,int currentUser);
void createTweet(TwitterSys* System,int currentUser);

int main() {
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
        setvbuf(stdout,NULL, _IONBF,0);
        printf("\nPlease choose from the 6 options. \n(1) Follow Someone. \n(2) UnFollow Someone. \n(3) Make a tweet."
               "\n(4) Display your news feed.\n(5) End turn.\n(6) Close program.");
        //checks for non-integer inputs
        while (scanf("%d", &Selection) == 0) {
            printf("Please input a number between 1-6\n\n");
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

    User *ActiveUser = System->allUsers[currentUser];
    char tempNotFollowing[24][16];
    int i =0;
    printf("\nThese are all the users you can follow:");
    //display all possible users to follow
    while ( i < System->numUsers) {
        //checks if the ith username in the system is in the array of activeUser's following
        for (int j = 0; j < (ActiveUser->numFollowing)+1; j++) {
            if(strcmp(System->allUsers[i]->username,ActiveUser->Following[j])==0||currentUser==i) {
                //if it matches skip it by incrementing i and start check again with j=0;
                i++;
                j = 0;
            }
        }
        if(i < System->numUsers) {
            printf("\n%s", System->allUsers[i]->username);
            strcpy(tempNotFollowing[i],System->allUsers[i]->username);
            i++;
        }
    }

    printf("\nSimply type the name of the user you want to follow");
    char userInput[15];
    fflush(stdin);
    fgets(userInput,15,stdin);
    userInput[strlen(userInput)-1]='\0';

    i=0;
    while(i<System->numUsers){
        //uses the array of valid targets to check if the user selected a vaild input
        if(strcmp(userInput,tempNotFollowing[i])==0){
            printf("\nNow following %s",userInput);
            strcpy(ActiveUser->Following[i],userInput);
            strcpy(System->allUsers[i]->Followers[currentUser],ActiveUser->username);
            System->allUsers[i]->numFollowers+=1;
            ActiveUser->numFollowing+=1;
            break;
        }
        i++;
        // if the loop gets to the end it prompts the user to make a new input
        if(i==System->numUsers){
            i=0;
            fflush(stdin);
            printf("\nError trying again. Please make sure the user is in the list of users you can follow");
            fgets(userInput,15,stdin);
            userInput[strlen(userInput)-1]='\0';
        }
    }
}

void unFollow(TwitterSys *System,int currentUser){
    //display all possible users to follow
    User *ActiveUser = System->allUsers[currentUser];
    int i=0;
    char userInput[15];
    if(ActiveUser->numFollowing<1){
        printf("\nYou arn't following anyone nothing to do here");
    }else {
        printf("\nThese are all the users you can unfollow:");
        for (int j = 0; j < 24; ++j) {
            if(strlen(ActiveUser->Following[j])>0) {
                printf("\n%s", ActiveUser->Following[j]);
            }
        }

        printf("\nSimply type the name of the user you want to unfollow");
        fflush(stdin);
        memset(userInput,0,sizeof(char[15]));
        fgets(userInput, 15, stdin);
        userInput[strlen(userInput) - 1] = '\0';

        while (i < ActiveUser->numFollowing) {
            if (strcmp(userInput, ActiveUser->Following[i]) == 0) {
                printf("\nNow not following %s", userInput);
                memset(ActiveUser->Following[i],0,strlen(ActiveUser->Following[i]));
                memset(System->allUsers[i]->Followers[currentUser], 0, strlen(System->allUsers[i]->Followers[currentUser]));
                System->allUsers[i]->numFollowers -= 1;
                ActiveUser->numFollowing -= 1;
                break;
            }
            i++;
            if (i == ActiveUser->numFollowing) {
                i = 0;
                fflush(stdin);
                printf("\nPlease input a user name correctly");
                fgets(userInput, 15, stdin);
                userInput[strlen(userInput) - 1] = '\0';
            }
        }
    }
}

void createTweet(TwitterSys* System,int currentUser){
    tweet *newTweet;
    tweet *prevTweet=NULL;
    tweet *currTweet=NULL;

    //assign space for the new tweet
    if((newTweet=malloc(sizeof(tweet)))==NULL){//check if space is available
        printf("Error creating new tweet");
        return;
    }else{
        //adds users name to the tweet
        strcpy( System->allUsers[currentUser]->username, newTweet->author);
        newTweet->nextTwt=NULL;//ends the list

        printf("Type what you want to tweet you have 280 character limit");
        fflush(stdin);
        fgets(newTweet->text,280,stdin);
        //makes sure string has termination char
        newTweet->text[strlen(newTweet->text)-1]='\0';

        if(System->firstTwt==NULL){//checks if there are no tweets
            System->firstTwt=newTweet;
        }else {
            do {
                //move two pointers till we find the end of the linked list
                prevTweet = System->firstTwt;
                currTweet = prevTweet->nextTwt;
            } while (currTweet != NULL);
            prevTweet->nextTwt = newTweet;
        }
        printf("Tweet successfully created.");
    }
}
