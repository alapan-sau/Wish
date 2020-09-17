#include "main.h"

void sigchld_handler(int signum)                                                // signal Handler
{
    pid_t pid;
    int   status;
    pid = waitpid(-1, &status, WNOHANG);
    if(pid!=-1){
        for(ll i=0;i<jobtot;i++){
            if((ll)pid==jobindex[i]){
                jobstat[i]=-1;
                printf(" Process %s with process ID [%lld] stopped with exit status %d\n",jobarr[i],(ll)pid,status);
                break;
            }
        }
    }
}