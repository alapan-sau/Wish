#include "main.h"

void history(ll n, char *commarg[]){
    ll total=0;
    if(n==1){
        total=5;
    }
    else{
        if(strlen(commarg[1])==1){
            total = commarg[1][0]-'0';
        }
        else total = (commarg[1][0]-'0')*10 + (commarg[1][1]-'0');
    }
    if(total > hisnum){
        total=hisnum;
    }
    ll iter=total;
    for(ll i=total-1;i>=0;i--){
        if(strcmp(historyarr[i],"")!=0){
            printf(" %lld.\t%s",iter,historyarr[i]);
            iter--;
        }
    }
}
