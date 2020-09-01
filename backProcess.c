#include "main.h"

void backProcess(ll n, char *commarg[]){
    ll forkReturn = fork();
    if(forkReturn==0){                                                // background/child process
        commarg[n-1]=NULL;
        execvp(commarg[0],commarg);
        exit(0);
    }
    else{
        printf("%d started\n",getpid());
        return;
    }
}