#include "main.h"

void backProcess(ll n, char *commarg[]){
    ll forkReturn = fork();
    if(forkReturn==0){                                                // background/child process
        commarg[n-1]=NULL;
        pid_t pid = getpid();
        execvp(commarg[0],commarg);
        exit(0);
    }
    else{
        ll len = strlen(commarg[0]);
        jobindex[jobtot]=forkReturn;
        jobs[jobtot] = malloc(len * sizeof(char));
        strcpy(jobs[jobtot],commarg[0]);
        jobtot++;
        printf("[%lld] started %s\n",jobindex[jobtot-1],jobs[jobtot-1]);
        return;
    }
}