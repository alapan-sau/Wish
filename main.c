#include "main.h"
#include "backProcess.h"
#include "foreProcess.h"
#include "history.h"
#include "ls.h"
#include "pinfo.h"
#include "sigchld_handler.h"
#include "cd.h"
#include "nightswatch.h"
#include "util.h"

void loadhistory(){
    FILE * hf =  fopen("historyfile.txt","r");
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
        FILE * hf = fopen("historyfile.txt","w");
        fclose(hf);
    }
}

void updatehistory(){
    if(strcmp(command,"")==0) return;
    if(strcmp(command,historyarr[0])==0) return;
    if(hisnum<20) hisnum++;
    for(ll i=18; i>=0; i--){
        strcpy(historyarr[i+1],historyarr[i]);
    }
    strcpy(historyarr[0],command);
    FILE * hf = fopen("historyfile.txt","w");
    if(hf){
        for(ll i=0;i<hisnum;i++){
            fprintf(hf,"%s",historyarr[i]);
        }
        fclose(hf);
    }
    return;
}

void getcurdir(){                                               // stores the current dir to currdir
    getcwd(currdir,MA);
    tilda_adder(currdir);
    return;
}


void execute_command(){                                                 // command handler

    char *allcommands[MA];
    allcommands[0] = strtok(command,";\n");
    ll index = 0;
    while(allcommands[index]!=NULL){
        allcommands[++index] = strtok(NULL,";\n");
    }
    ll totalcommands = index;

    for(ll task=0;task<totalcommands;task++){
        char *commarg[MA];
        commarg[0] = strtok(allcommands[task]," ");
        index = 0;
        while(commarg[index]!=NULL){
            commarg[++index] = strtok(NULL," ");
        }
        ll totalcommarg = index;



        if(strcmp(commarg[totalcommarg-1],"&")==0){
            backProcess(totalcommarg,commarg);
            continue;
        }
        if(strcmp(commarg[0],"cd")==0){         // impl err
            cd(totalcommarg,commarg);
        }
        else if(strcmp(commarg[0],"mkdir")==0){   // impl
            mkdir(commarg[1],0777);
        }
        else if(strcmp(commarg[0],"pwd")==0){    // impl err
            if(totalcommarg>1){
                printf("pwd : too many arguments\n");
                continue;
            }
            getcurdir();
            printf("%s\n",currdir);
        }
        else if(strcmp(commarg[0],"echo")==0){         //  nothing done
            for(ll i=1;i<totalcommarg;i++){
                printf("%s ",commarg[i]);
            }
            printf("\n");
        }
        else if(strcmp(commarg[0],"ls")==0){            // impl error
            ls(totalcommarg,commarg);
        }
        else if(strcmp(commarg[0],"q")==0){
            exit(0);
        }
        else if(strcmp(commarg[0],"pinfo")==0){
            pinfo(totalcommarg,commarg);
        }
        else if(strcmp(commarg[0],"history")==0){
            history(totalcommarg,commarg);
        }
        else if(strcmp(commarg[0],"nightswatch")==0){
            nightswatch(totalcommarg,commarg);
        }
        else{
            foreProcess(totalcommarg,commarg);
            continue;
        }
    }
}

void getcommand(){                                                  // fetches command from terminal
    size_t size_command = 100;

    command = (char *)malloc(size_command);
    getline(&command, &size_command, stdin);
}

void gethomedir(){                                                  // stores home dir to homedir
    getcwd(homedir,MA);
    return;
}

void reference(){                                                    // prompt fx
    char username[MA];
    char hostname[MA];
    char reference[MA];
    getlogin_r(username,MA);
    gethostname(hostname,MA);
    getcurdir();
    sprintf(reference,"\033[0;91m<%s@%s:\033[0;93m%s\033[0;91m> \033[0;97m",username,hostname,currdir);
    printf("%s",reference);
}

int main(){
    hisnum = 0;
    jobtot=0;
    loadhistory();
    gethomedir();
    while(1){
        signal(SIGCHLD, sigchld_handler);
        reference();
        getcommand();
        updatehistory();
        execute_command();
    }
}