#include "main.h"
#include "backProcess.h"
#include "foreProcess.h"
#include "history.h"
#include "ls.h"
#include "pinfo.h"
#include "sigchld_handler.h"
#include "cd.h"
#include "nightswatch.h"
#include "jobs.h"
#include "kjob.h"
#include "overkill.h"
#include "fg.h"
#include "util.h"

void command_handler(char *curr_command){
    char *commarg[MA];
    ll index = 0;

///////////////////////////////////////////
    commarg[0] = strtok(curr_command," \t");
    index = 0;
    while(commarg[index]!=NULL){
        commarg[++index] = strtok(NULL," \t");
    }
    ll totalcommarg = index;
/////////////////////////////////////////////

    if(strcmp(commarg[totalcommarg-1],"&")==0){
        backProcess(totalcommarg,commarg);
        return;
    }
    else if(strcmp(commarg[0],"cd")==0){
        cd(totalcommarg,commarg);
    }
    else if(strcmp(commarg[0],"pwd")==0){
        if(totalcommarg>1){
            printf("pwd : too many arguments\n");
            return;
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
        overkill();
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
    else if(strcmp(commarg[0],"setenv")==0){    // test on linux!
        if(totalcommarg>3){
            printf("too many arguments!\n");
            return;
        }
        else if(totalcommarg<3) commarg[2]="";

        if(setenv(commarg[1],commarg[2],1)<0){
            perror("setenv ");
        }
    }
    else if(strcmp(commarg[0],"unsetenv")==0){
        if(totalcommarg>2){
            printf("too many arguments!\n");
            return;
        }
        if(unsetenv(commarg[1])<0){
            perror("unsetenv ");
        }
    }
    else if(strcmp(commarg[0],"jobs")==0){
        jobs(totalcommarg,commarg);
    }
    else if(strcmp(commarg[0],"kjob")==0){
        kjob(totalcommarg,commarg);
    }
    else if(strcmp(commarg[0],"overkill")==0){
        overkill();
    }
    else if(strcmp(commarg[0],"fg")==0){
        fg(totalcommarg,commarg);
    }
    else{
        foreProcess(totalcommarg,commarg);
        return;
    }
}
void piper(char *pipe_command){
    char *unpiped_commands[MA];

////////////////////////////////////////////////////
    unpiped_commands[0] = strtok(pipe_command,"|");
    ll index = 0;
    while(unpiped_commands[index]!=NULL){
        unpiped_commands[++index] = strtok(NULL,"|");
    }
    ll total_unpiped_commands = index;
//////////////////////////////////////////////////////
    int actual_cin = dup(0);
    int actual_cout = dup(1);

    int fd[2][2];

    for(ll i=0;i<total_unpiped_commands;i++){

        if(i==(total_unpiped_commands-1)){
            command_handler(unpiped_commands[i]);
            if(i!=0)close(fd[!(i%2)][0]);
        }
        else{
            if(pipe(fd[i%2]) == -1){
		        printf("Shit\n");
		        exit(0);
	        }
            pid_t forkReturn = fork();
            if(forkReturn<0){
		        printf("Shit\n");
		        exit(0);
            }
            if(forkReturn==0){
                close(fd[i%2][0]);
                dup2(fd[i%2][1], 1);
		        command_handler(unpiped_commands[i]);
		        close(fd[i%2][1]);
		        exit(0);
            }
            else{
                close(fd[i%2][1]);
                waitpid(forkReturn, NULL, 0);
                dup2(fd[i%2][0], 0);
                if(i!=0)close(fd[!(i%2)][0]);
            }
        }
    }
    dup2(actual_cout,1);
    dup2(actual_cin,0);
}

void execute_command(){                                                 // command handler
    char *allcommands[MA];
///////////////////////////////////////////////
    allcommands[0] = strtok(command,";\n");
    ll index = 0;
    while(allcommands[index]!=NULL){
        allcommands[++index] = strtok(NULL,";\n");
    }
    ll totalcommands = index;
////////////////////////////////////////////////


    for(ll task=0;task<totalcommands;task++){
        piper(allcommands[task]);
    }
}