#include "main.h"
#include "util.h"

void kjob(ll n, char * commarg[]){
    if(n>3){
        printf("kjob : too many arguments!\n");
    }
    else if(n<3){
        printf("kjob : too few arguments!\n");
    }
    else{
        ll index = atoi(commarg[1]);
        pid_t pid = jobindex[index-1];
        ll sig = atoi(commarg[2]);
        if(index>jobtot){
            printf("kjob : invalid process!\n");
            return;
        }
        if(kill(pid,sig)<0){
            perror("kjob ");
        }
    }
}