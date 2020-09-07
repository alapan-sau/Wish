#include "main.h"

void foreProcess(ll n,char *commarg[]){
    ll forkReturn = fork();
    if(forkReturn<0){
        printf("Oops! Unable to fork!\n");
        return;
    }
    if(forkReturn==0){                                                // foreground/child process
        commarg[n]=NULL;
        ll ret = execvp(commarg[0],commarg);
        if(ret<0){
            printf("Oops! Invalid command!\n");
        }
        exit(0);
    }
    else{                                                              // parent process
        int status;
        waitpid(forkReturn,&status,WUNTRACED);                         // waits for child process(fg)
        return;
    }
}