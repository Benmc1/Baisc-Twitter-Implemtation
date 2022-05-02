//
// Created by benmc on 02/05/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Twt+News.h"
#include "Structs.h"

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

    if(System->firstTwt == NULL){//checks if there are any tweets
        printf("\nCouldn't find any tweets");
        return;
    }
    currTweet= System->firstTwt;//first sets the pointers
    printf("\nHere are the latest available tweets from "
           "you and people you follow:");
    do {
        nextTweet = (tweet *) currTweet->nextTwt;
        //checks if the users is following the author of the current tweet
        while (x<System->numUsers){
            if((strcmp(currTweet->author,System->allUsers[currentUser]->Following[x]))==0){
                printf("\n%s:\n\t%s\n",currTweet->author,currTweet->text);
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
        x=0;
    }while(nextTweet != NULL && i < 10 );
}
