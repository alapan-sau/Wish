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
        if(strcmp(commarg[0],"cd")==0){
            cd(totalcommarg,commarg);
        }
        else if(strcmp(commarg[0],"pwd")==0){
            if(totalcommarg>1){
                printf("pwd : too many arguments\n");
                continue;
            }
            getcurdir();
            tilda_adder(currdir);
            printf("%s\n",currdir);
            getcurdir();
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
        else if(strcmp(commarg[0],"quit")==0){
            for(ll i=0;i<jobtot;i++){
                // printf("%lld\n",jobindex[i]);
                kill(jobindex[i], SIGKILL);     // killing background processes to solve vim errors!
            }
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