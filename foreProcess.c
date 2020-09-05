#include "main.h"

void foreProcess(ll n,char *commarg[]){
    ll forkReturn = fork();
    if(forkReturn==0){                                                // foreground/child process
        commarg[n]=NULL;
        execvp(commarg[0],commarg);
        exit(0);
    }
    else{
        wait(NULL);
        return;
    }
}