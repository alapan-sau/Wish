#include "main.h"
#include "util.h"

void fg(ll n, char *commarg[]){
    if(n>2){
        printf("fg : too many arguments!\n");
        return;
    }
    else if(n<1){
        printf("fg : too few arguments!\n");
        return;
    }
    else{
        ll index = atoi(commarg[1]);
        if(index > jobtot){
            printf("fg : Invalid process!\n");
            return;
        }
        pid_t pid = jobindex[index];
        if(kill(pid,SIGCONT)<0){
            perror("fg ");
        }
        tcsetpgrp(0,pid);
    }
}