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