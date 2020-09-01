#include "main.h"

void pinfo(ll n, char *commarg[]){                                      // pinfo
    pid_t pid;
    if(n==1) pid = getpid();
    else pid = atoi(commarg[1]);
    char procfile[1000];
    char execfile[1000];
    sprintf(procfile, "/proc/%d/stat", pid);
    sprintf(execfile, "/proc/%d/exe", pid);

    char status;
    ll memory;
    FILE  *procfd = fopen(procfile, "r");
    fscanf(procfd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lld %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status, &memory);
    fclose(procfd);
    printf("PID -- %d\n", pid);
    printf("Process Status -- %c\n", status);
    printf("Memory -- %lld\n", memory);

    char procadd[MA];
    int len = readlink(execfile, procadd, sizeof(procadd));
    procadd[len] = '\0';

    len = strlen(homedir);
    ll index=0;
    for(index=0;index<len;index++){
        if(homedir[index]!=procadd[index]){
            printf("Executable Path --  %s\n", procadd);
            return;
        }
    }
    char address[MA];
    strcpy(address,"~");
    strcat(address,procadd+strlen(homedir));
    printf("Executable Path --  %s\n", address);
}