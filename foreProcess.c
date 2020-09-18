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
        latest_fore_pid = forkReturn;
        strcpy(latest_fore_process_name,commarg[0]); 
        waitpid(forkReturn,&status,WUNTRACED);                         // waits for child process(fg)
        latest_fore_pid=-1;

        return;
    }
}