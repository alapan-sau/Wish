#include "main.h"

void bg(ll n, char *commarg[]){
    if(n>2){
        fprintf(stderr,"fg : too many arguments!\n");
        latest_status=0;
        return;
    }
    else if(n<=1){
        fprintf(stderr,"fg : too few arguments!\n");
        latest_status=0;
        return;
    }
    else{
        ll index = atoi(commarg[1]);
        if(index > jobtot){
            fprintf(stderr,"fg : Invalid process!\n");
            latest_status=0;
            return;
        }
        pid_t child_pid = jobindex[index-1];
        if(kill(child_pid,SIGCONT)<0){
            perror("bg ");
            latest_status=0;
            return;
        }
        return;
    }
}