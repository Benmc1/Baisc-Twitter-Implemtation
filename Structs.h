//
// Created by benmc on 02/05/2022.
//

#ifndef COMP10050_STRUCTS_H
#define COMP10050_STRUCTS_H

#define MAXUSERS 24
#define MAXUSERNAME 16
typedef struct  {
    char username[MAXUSERS];
    unsigned int numFollowers;
    unsigned int numFollowing;
    char Followers[MAXUSERS][MAXUSERNAME];
    char Following[MAXUSERS][MAXUSERNAME];
}User ;

typedef struct {
    char author[MAXUSERNAME];
    char text[281];
    struct tweet *nextTwt;
}tweet;

typedef struct {
    User *allUsers[MAXUSERS];
    int numUsers;
    tweet *firstTwt;
}TwitterSys;

#endif //COMP10050_STRUCTS_H
