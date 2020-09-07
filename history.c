#include "main.h"

void loadhistory(){                           // initial call to detect/read/create historytext.file
    char HISTORYFILE[MA];
    sprintf(HISTORYFILE,"%s/historyfile.txt",homedir);
    FILE * hf =  fopen(HISTORYFILE,"r");
    if(hf){
        int pos;
        ll i = 0;
        while ((i<20) && fgets(historyarr[i], MA, hf)!= NULL){
            i++;
        }
        hisnum = i;
        for(;i<20;i++) strcpy(historyarr[i],"");
        fclose(hf);
    }
    else{
        FILE * hf = fopen(HISTORYFILE,"w");
        fclose(hf);
    }
}

void updatehistory(){                           // updates history after every command
    char HISTORYFILE[MA];
    sprintf(HISTORYFILE,"%s/historyfile.txt",homedir);
    if(strcmp(command,"")==0) return;
    if(strcmp(command,historyarr[0])==0) return;
    if(hisnum<20) hisnum++;
    for(ll i=18; i>=0; i--){
        strcpy(historyarr[i+1],historyarr[i]);
    }
    strcpy(historyarr[0],command);
    FILE * hf = fopen(HISTORYFILE,"w");
    if(hf){
        for(ll i=0;i<hisnum;i++){
            fprintf(hf,"%s",historyarr[i]);
        }
        fclose(hf);
    }
    return;
}

void history(ll n, char *commarg[]){           // history function
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
    if(total>10 || total<1)
    {
        printf("Put a number between 1 to 10!\n");
        return;
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
