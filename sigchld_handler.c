#include "main.h"

void sigchld_handler(int signum)                                                // signal Handler
{
    pid_t pid;
    int   status;
    pid = waitpid(-1, &status, WNOHANG);
    if(pid!=-1){
        for(ll i=0;i<jobtot;i++){
            if((ll)pid==jobindex[i]){
                printf(" Process %s with process ID [%lld] stopped with exit status %d\n",jobs[i],(ll)pid,status);
                break;
            }
        }
    }
}