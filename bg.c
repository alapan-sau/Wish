#include "main.h"

void bg(ll n, char *commarg[]){
    if(n>2){
        printf("fg : too many arguments!\n");
        return;
    }
    else if(n<=1){
        printf("fg : too few arguments!\n");
        return;
    }
    else{
        ll index = atoi(commarg[1]);
        if(index > jobtot){
            printf("fg : Invalid process!\n");
            return;
        }
        pid_t child_pid = jobindex[index-1];
        if(kill(child_pid,SIGCONT)<0){
            perror("bg ");
            return;
        }
        return;
    }
}