//
// Created by benmc on 02/05/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Delete.h"

int deleteUser(TwitterSys* System,int currentUser) {
    char Input;

    printf("\nAre you sure you want to delete your account."
           "Type Y to continue and anything else to exit");
    scanf("%c", &Input);
    fflush(stdin);

    if (Input != 'Y') {//returns to menu
        printf("\n Exiting...\n");
        return 0;
    } else {

        tweet *prevTweet = NULL;
        tweet *currTweet = NULL;
        tweet *tempTweet = NULL;

        //removing tweets from stack
        if (System->firstTwt != NULL) {//checks if there are any tweets

            while(System->firstTwt != NULL &&(strcmp(System->firstTwt->author, System->allUsers[currentUser]->username)) == 0){//check if the first tweet is form the current user
                tempTweet = System->firstTwt; //hold the tweet to be deleted
                System->firstTwt = (tweet *) System->firstTwt->nextTwt;      //assigns the system ptr to next ptr
                free(tempTweet);
            }

            currTweet = System->firstTwt;//assign pointers

            while ( currTweet != NULL){
                if ((strcmp(currTweet->author, System->allUsers[currentUser]->username)) == 0) {//check if the author is the current user
                    prevTweet->nextTwt = currTweet->nextTwt;
                    tempTweet = currTweet;
                    currTweet = (tweet *) prevTweet->nextTwt;
                    free(tempTweet);
                } else{
                    prevTweet = currTweet;
                    currTweet = (tweet *) prevTweet->nextTwt;
                }
            }
        }

        int x = 0;
        int j = 0;

        // removing from followers+following
        while (x < System->allUsers[currentUser]->numFollowing){//runs for as many following the deleted account has
            //runs till its find the pos of the person they're following
            if (System->allUsers[currentUser]->Following[j] != NULL && System->allUsers[currentUser]->Following[j][0]!='\0'){
                //goes to that user and sets the pos of the deleted user to zero
                memset(System->allUsers[j]->Followers[currentUser],0,sizeof (System->allUsers[j]->Followers[j]));
                System->allUsers[j]->numFollowers--;// decrements the followers count
                x++;
            }
            j++;
        }
        x = 0;
        j = 0;
        while (x < System->allUsers[currentUser]->numFollowers) {
            if (System->allUsers[currentUser]->Followers[j] != NULL &&
                System->allUsers[currentUser]->Followers[j][0] != '\0') {//runs till its find the pos of the person following the deleted user
                //goes to that user and sets the pos of the deleted user to zero
                memset(System->allUsers[j]->Following[currentUser], 0,
                       sizeof(System->allUsers[j]->Following[currentUser]));
                System->allUsers[j]->numFollowing--;// decrements the followers count
                x++;
            }
            j++;
        }

        //removing the user from the System list
        free(System->allUsers[currentUser]);
        System->allUsers[currentUser]=NULL;
        return 1;
    }
}