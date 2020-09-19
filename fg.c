#include "main.h"
#include "util.h"

void fg(ll n, char *commarg[]){
    if(n>2){
        printf("fg : too many arguments!\n");
        return;
    }
    else if(n<=1){
        printf("fg : too few arguments!\n");
        return;
    }
    else{
        signal(SIGTTOU,SIG_IGN);
        signal(SIGTTIN,SIG_IGN);

        ll index = atoi(commarg[1]);
        if(index > jobtot){
            printf("fg : Invalid process!\n");
            return;
        }
        pid_t child_pgid = getpgid(jobindex[index-1]);
        pid_t child_pid = jobindex[index-1];
        pid_t curr_pgid = getpgrp();

        if(kill(child_pid,SIGCONT)<0){
            perror("fg ");
            return;
        }

        tcsetpgrp(STDIN_FILENO,child_pgid);
        int status;
        waitpid(child_pgid,&status,WUNTRACED);
        tcsetpgrp(0,curr_pgid);
        signal(SIGTTOU,SIG_DFL);
        signal(SIGTTIN,SIG_DFL);
        return;
    }
}