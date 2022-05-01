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
void newsFeed(TwitterSys* System,int currentUser);
void deleteUser(TwitterSys* System,int currentUser);

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
        printf("\nPlease choose from the 6 options. \n(1) Follow Someone. "
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
                deleteUser(System,currentUser);
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

    printf("\nSimply type the name of the user you want to follow\n");
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
            printf("\nError trying again.\n Please make sure the user is in the list of users you can follow\n");
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

    //assign space for the new tweet
    if((newTweet=malloc(sizeof(tweet)))==NULL){//check if space is available
        printf("\nError creating new tweet");
        return;
    }else{
        //adds users name to the tweet
        strcpy( newTweet->author, System->allUsers[currentUser]->username);
        newTweet->nextTwt=NULL;//ends the list

        printf("\nType what you want to tweet you have 280 character limit:\n");
        fflush(stdin);
        fgets(newTweet->text,281,stdin);
        //makes sure string has termination char
        if((newTweet->text[strlen(newTweet->text) - 1]) == '\n'){
            newTweet->text[strlen(newTweet->text) - 1] = '\0';
        }
        if(System->firstTwt==NULL){//checks if there are no tweets
            System->firstTwt=newTweet;
        }else {
            //sets the new tweet to the top and links to the previous first tweet
            newTweet->nextTwt = (struct tweet *) System->firstTwt;
            System->firstTwt = newTweet;
        }
        printf("\nTweet successfully created.");
    }
}

void newsFeed(TwitterSys* System,int currentUser){
    int i=0;// to keep track of num of tweets printed
    int x=0;
    tweet *nextTweet=NULL;
    tweet *currTweet=NULL;

    printf("\nHere are the latest available tweets from "
           "you and people you follow:");

    if(System->firstTwt ==NULL){//checks if there are any tweets
        printf("\nCouldn't find any tweets");
        return;
    }
    currTweet= System->firstTwt;//first sets the pointers
    do {
        nextTweet = (tweet *) currTweet->nextTwt;
        //checks if the users is following the author of the current tweet
        while (x<System->numUsers){
          if((strcmp(currTweet->author,System->allUsers[currentUser]->Following[x]))==0){
              printf("\n%s:\n\t%s",currTweet->author,currTweet->text);
              i++;
          }
          x++;
        }
        //checks if the current user is the author of the current tweet
        if ((strcmp(currTweet->author,System->allUsers[currentUser]->username))==0){
            printf("\nYou:\n\t%s\n",currTweet->text);
            i++;
        }
        currTweet= nextTweet;//moves through the list

    }while(nextTweet != NULL && i < 10 );
}

void deleteUser(TwitterSys* System,int currentUser) {
    char Input;

    printf("\nAre you sure you want to delete your account."
           "Type Y to continue and anything else to exit");
    scanf("%c", &Input);

    if (Input != 'Y') {
        //returns to menu
        printf("\n Exiting...\n");
        return;
    } else {
        tweet *prevTweet = NULL;
        tweet *currTweet = NULL;
        tweet *tempTweet = NULL;

        //removing tweets from stack
        if (System->firstTwt != NULL) {//checks if there are any tweets

            while((strcmp(System->firstTwt->author, System->allUsers[currentUser]->username)) == 0){//check if the first tweet is form the current user
                    tempTweet = System->firstTwt; //hold the tweet to be deleted
                    System->firstTwt = (tweet *) System->firstTwt->nextTwt;      //assigns the system ptr to next ptr
                    free(tempTweet);
                }

            currTweet = (tweet *) System->firstTwt->nextTwt;//assign pointers
            prevTweet = System->firstTwt;

            while ( currTweet != NULL){
                if ((strcmp(currTweet->author, System->allUsers[currentUser]->username)) == 0) {//check if the author is the current user
                        prevTweet->nextTwt = currTweet->nextTwt;
                        free(currTweet);
                        currTweet = (tweet *) prevTweet->nextTwt;
                }
            }
        }
        int i = 0;
        int x = 0;
        int j = 0;
        // removing from followers+following
        while(i < System->numUsers){
            while (x < System->allUsers[currentUser]->numFollowing){//runs for as many following the deleted account has
                if (System->allUsers[currentUser]->Following[j][0]!='\0'){//runs till its find the pos of the person they're following
                    //goes to that user and sets the pos of the deleted user to zero
                    memset(System->allUsers[j]->Followers[currentUser],0,strlen(System->allUsers[j]->Followers[currentUser]));
                    System->allUsers[j]->numFollowers--;// decrements the followers count
                    x++;
                }
                j++;
            }
            x = 0;
            j = 0;
            while (x < System->allUsers[currentUser]->numFollowers){
                if (System->allUsers[currentUser]->Followers[j][0]!='\0'){//runs till its find the pos of the person following the deleted user
                    //goes to that user and sets the pos of the deleted user to zero
                    memset(System->allUsers[j]->Following[currentUser],0,strlen(System->allUsers[j]->Following[currentUser]));
                    System->allUsers[j]->numFollowing--;// decrements the followers count
                    x++;
                }
                j++;
            }
        }

        //removing the user from the System list
        free(System->allUsers[currentUser]);
        System->allUsers[currentUser]=NULL;
    }
}