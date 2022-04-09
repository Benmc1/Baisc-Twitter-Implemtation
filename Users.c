//
// Created by benmc on 06/04/2022.
//

#include "Users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TwitterSys * createUsers(){
    unsigned int x=0;
    char testNames[][16]={"Alpha","Beta","Chi","Delta","Epsilon","Phi","Gamma","Eta","Iota","Kappa","Lambda","Mu","Nu","Omicron","Pi","Theta","Rho","Sigma","Tau","Upsilon","Omega","Xi","Psi","Zeta"};

    printf("\nInput how many users you would like to create");
    //makes sure user inputs a number
    while (scanf("%d", &x) == 0||x<=0||x>=25) {
        printf("Please input a number between 1-24\n");
        scanf("%*s", &x);
    }
    fflush(stdin);
    printf("\nCreating  users");

    TwitterSys *System = malloc(sizeof (TwitterSys));
    if (System==NULL){
        printf("\nCould not create system");
        return 0;
    }else{
        System->numUsers=x;
        System->firstTwt=NULL;
        for (int j = 0; j < x; ++j) {
            System->allUsers[j]= malloc(sizeof(User));
            if (System->allUsers[j]==NULL){
                printf("\nCould not create User %d",j);
            }else {
                strcpy((System->allUsers[j]->username), testNames[j]);
                System->allUsers[j]->numFollowing=0;
                System->allUsers[j]->numFollowers=0;
                memset(System->allUsers[j]->Following,0,sizeof(System->allUsers[j]->Following) );
            }
        }
    }
    return System;
}
void displayUserData(User*n){
    printf("\n---------------------------------------------");
    printf("\nHello %s\nYou have:%d followers and are following %d people."
           ,n->username,n->numFollowers,n->numFollowing);
}