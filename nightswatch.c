#include "main.h"

int endWatch(ll n){
    struct timeval tv;
    tv.tv_usec = 0;
    tv.tv_sec = n;

    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    int ret = select(1,&rfds, NULL, NULL, &tv);
    if(ret > 0){
        size_t size_c = 3;
        char *c;
        c = (char *)malloc(size_c);
        getline(&c, &size_c, stdin);
        if (c[0] == 'q'){
            printf("Bye Bye\n");
            return 1;
        }
        else{
            printf("Press q to enter\n");
        }
    }
    return 0;
}

void interrupt(char * commarg[]){
    ll n = atoi(commarg[2]);
    FILE * id = fopen("/proc/interrupt","r");
    char lineCPU[MA];
    fgets(lineCPU, MA, id);
    printf("%s\n",lineCPU);
    fclose(id);
    while(1){
        id = fopen("/proc/interrupt","r");
        char lineInterrupt[MA];
        for(ll i=0;i<3;i++) fgets(lineInterrupt, MA, id);
        printf("%s\n",lineCPU);
        fclose(id);
        if(endWatch(n)) return;
    }
}