#include "main.h"

void sigchld_handler(int signum)                                                // signal Handler
{
    pid_t pid;
    int   status;
    pid = waitpid(-1, &status, WNOHANG);
    if(pid!=-1){
        for(ll i=0;i<jobtot;i++){
            if((ll)pid==jobindex[i] && jobstat[i]!=-1){
                jobstat[i]=-1;
                fprintf(stderr," Process %s with process ID [%lld] stopped with exit status %d\n",jobarr[i],(ll)pid,status);
                reference();
                break;
            }
        }
    }
}

void sigint_handler(int signum)                                                // signal Handler
{
    signal(signum,SIG_IGN);
    latest_status=0;
}

void sigtstp_handler(int signum)                                                // signal Handler
{
    signal(signum,SIG_IGN);
    latest_status=0;
}