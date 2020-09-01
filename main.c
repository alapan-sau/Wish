#include "main.h"
#include "backProcess.h"
#include "foreProcess.h"
#include "history.h"
#include "ls.h"
#include "pinfo.h"
#include "sigchld_handler.h"
#include "cd.h"

void getcurdir(){                                                           // stores the current dir to currdir
    getcwd(currdir,MA);
    if(strcmp(currdir,homedir)==0) strcpy(currdir,"~");
    else{
        ll len = strlen(homedir);
        ll index=0;
        for(index=0;index<len;index++){
            if(homedir[index]!=currdir[index])
                return;
        }
        ll i=1;
        len = strlen(currdir);
        for(;index<=len;index++,i++)
            currdir[i]=currdir[index];
        currdir[0]='~';
    }
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
        if(strcmp(commarg[0],"cd")==0){
            if(totalcommarg==1){cd("~");}
            else cd(commarg[1]);
        }
        else if(strcmp(commarg[0],"mkdir")==0){
            mkdir(commarg[1],0777);
        }
        else if(strcmp(commarg[0],"pwd")==0){
            getcurdir();
            printf("%s\n",currdir);
        }
        else if(strcmp(commarg[0],"echo")==0){
            for(ll i=1;i<totalcommarg;i++){
                printf("%s ",commarg[i]);
            }
            printf("\n");
        }
        else if(strcmp(commarg[0],"ls")==0){
            ls(totalcommarg,commarg);
        }
        else if(strcmp(commarg[0],"q")==0){
            exit(0);
        }
        else if(strcmp(commarg[0],"pinfo")==0){
            pinfo(totalcommarg,commarg);
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
    gethomedir();
    while(1){
        signal(SIGCHLD, sigchld_handler);
        reference();
        getcommand();
        execute_command();
    }
}