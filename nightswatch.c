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
            printf("Exit Succesfully\n");
            return 1;
        }
        else{
            printf("Press q to enter\n");
        }
    }
    return 0;
}

void interrupts(char * commarg[]){
    ll n = atoi(commarg[2]);
    FILE * id = fopen("/proc/interrupts","r");  // change . to /proc
    char lineCPU[MA];
    fgets(lineCPU, MA, id);
    printf("%s\n",lineCPU);
    fclose(id);

    ll lenCPU = strlen(lineCPU);
    for(ll i=lenCPU-1;i>=0;i--){
        if(lineCPU[i]==' ' || lineCPU[i]=='\n' || lineCPU[i]=='\t'){
            lineCPU[i]='\0';
        }
        else break;
    }
    lenCPU = strlen(lineCPU);
    while(1){
        id = fopen("/proc/interrupts","r"); // change . to /proc
        char lineInterrupts[3][MA];
        for(ll i=0;i<3;i++) fgets(lineInterrupts[i], MA-1, id);
        lineInterrupts[2][lenCPU] = '\0';
        for(ll i=0;i<lenCPU;i++){
            if(lineInterrupts[2][i]==':'){
                lineInterrupts[2][i]=' ';
                lineInterrupts[2][i-1] = ' ';
                break;
            }
            else lineInterrupts[2][i]=' ';
        }
        printf("%s\n",lineInterrupts[2]);
        fclose(id);
        if(endWatch(n)) return;
    }
}

void newborn(char * commarg[]){ // change . to /proc
    ll n = atoi(commarg[2]);
    while(1){
        FILE * id = fopen("/proc/loadavg","r");
        ll proc_num;
        char arr[100];
        fscanf(id,"%s %s %s %s %lld",arr,arr,arr,arr,&proc_num);
        printf("%lld\n",proc_num);
        fclose(id);
        if(endWatch(n)) return;
    }
}
