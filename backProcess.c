#include "main.h"

void backProcess(ll n, char *commarg[]){
    ll forkReturn = fork();
    setpgrp();                                              // setting process ID to process grp ID;
    // setpgid(0,0);                                        // same thing can be done using
    if(forkReturn<0){
        printf("Oops! Unable to fork!\n");
        return;
    }
    if(forkReturn==0){                                                // background/child process
        commarg[n-1]=NULL;
        pid_t pid = getpid();
        ll ret = execvp(commarg[0],commarg);                          // executes executable files
        if(ret<0){
            printf("Oops! Invalid command!");
        }
        exit(0);
    }
    else{
        ll len = strlen(commarg[0]);                                   // parent process
        jobindex[jobtot]=forkReturn;                                   // push created child to jobs
        jobs[jobtot] = malloc(len * sizeof(char));
        if(command==NULL){
            printf("Oops! Memory Error!\n");
        }
        strcpy(jobs[jobtot],commarg[0]);
        jobtot++;
        printf("[%lld] started %s\n",jobindex[jobtot-1],jobs[jobtot-1]);
        return;
    }
}