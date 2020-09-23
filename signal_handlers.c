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
                fprintf(stderr," Process %s with process ID [%lld] stopped with exit status %d\n",jobarr[i],(ll)pid,status);
                break;
            }
        }
    }
}

void sigint_handler(int signum)                                                // signal Handler
{
    latest_status=0;
    if(latest_fore_pid<0){
        return;
    }
    kill(latest_fore_pid,SIGKILL);
}

void sigtstp_handler(int signum)                                                // signal Handler
{
    latest_status=0;
    if(latest_fore_pid<0){
        return;
    }
    ll len = strlen(latest_fore_process_name);                                   // parent process
    jobindex[jobtot]=latest_fore_pid;                                  // push created child to jobs
    jobarr[jobtot] = malloc(len * sizeof(char));
    if(command==NULL){
        fprintf(stderr,"Oops! Memory Error!\n");
        latest_status=0;
    }
    strcpy(jobarr[jobtot],latest_fore_process_name);
    jobstat[jobtot]=1;
    jobtot++;
}