//
// Created by benmc on 06/04/2022.
//

#include "Users.h"
#include <stdio.h>

void createUsers(){
    unsigned int x;
    int i=0;
  //  printf("Input how many users you would like to create");
//    fgets(x,1,stdin);
    printf("Creating 10 users");
    x=10;
    User Alpha={"Alpha",12,9};

}
void displayUserData(User*n){
    printf("\n---------------------------------------------");
    printf("\nHello %s\nYou have:%d followers and are following %d people."
           ,n->username,n->numFollowers,n->numFollowing);
}