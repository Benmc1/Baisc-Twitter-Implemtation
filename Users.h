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
    struct User *Followers[20];
    struct User *Following[20];
}User ;
void displayUserData(User *n);
void createUsers(void);