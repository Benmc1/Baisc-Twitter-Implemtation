//
// Created by benmc on 06/04/2022.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct  {
    char username[15];
    unsigned int numFollowers;
    unsigned int numFollowing;
    struct User *Followers[20];
    struct User *Following[20];
}User ;
typedef struct {
    char author[15];
    char text[280];
    struct tweet *nextTwt;
}tweet;

typedef struct {
    User allUsers[20];
    int numUsers;
    tweet *firstTwt;
}TwitterSys;
int main(){

}
