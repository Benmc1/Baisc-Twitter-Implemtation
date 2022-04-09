//
// Created by benmc on 06/04/2022.
//

#ifndef COMP10050_USERS_H
#define COMP10050_USERS_H

#endif //COMP10050_USERS_H

typedef struct  {
    char username[15];
    unsigned int numFollowers;
    unsigned int numFollowing;
    char Followers[24][15];
    char Following[24][15];
}User ;

typedef struct {
    char author[15];
    char text[280];
    struct tweet *nextTwt;
}tweet;

typedef struct {
    User *allUsers[24];
    int numUsers;
    tweet *firstTwt;
}TwitterSys;

void displayUserData(User *n);
TwitterSys * createUsers(void);
