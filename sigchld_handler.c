#include "main.h"

void sigchld_handler(int signum)                                                // signal Handler
{
    pid_t pid;
    int   status;
    // while ((pid = waitpid(-1, &status, WNOHANG)) != -1)
    // {
    //     printf("%d ended\n",pid);   // Or whatever you need to do with the PID
    // }
    pid = waitpid(-1, &status, WNOHANG);
    if(pid!=-1)printf("%d ended\n",pid);
}