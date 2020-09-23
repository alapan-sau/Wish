#include "main.h"

void foreProcess(ll n,char *commarg[]){
    ll forkReturn = fork();
    if(forkReturn<0){
        fprintf(stderr,"Oops! Unable to fork!\n");
        latest_status=0;
        return;
    }
    if(forkReturn==0){                                                // foreground/child process
        commarg[n]=NULL;
        ll ret = execvp(commarg[0],commarg);
        if(ret<0){
            fprintf(stderr,"Oops! Invalid command!\n");
            exit(1);
        }
        exit(0);
    }
    else{                                                              // parent process
        latest_fore_pid = forkReturn;
        strcpy(latest_fore_process_name,commarg[0]);
        int status;
        waitpid(forkReturn,&status,WUNTRACED);                         // waits for child process(fg)
        //printf("status is %d\n",status);
        if(status!=0) latest_status=0;
        latest_fore_pid=-1;
        return;
    }
}