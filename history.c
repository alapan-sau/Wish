#include "main.h"

void history(ll n, char *commarg[]){
    ll total=0;
    if(n==1){
        total=10;
    }
    else{
        total = commarg[1][1]-'0';
    }
    ll iter=1;
    for(ll i=1;i<total+1;i++){
        if(strcmp(historyarr[i],"")!=0){
            printf(" %lld.\t%s",iter,historyarr[i]);
            iter++;
        }
    }
}
