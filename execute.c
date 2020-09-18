#include "main.h"
#include "backProcess.h"
#include "foreProcess.h"
#include "history.h"
#include "ls.h"
#include "pinfo.h"
#include "signal_handlers.h"
#include "cd.h"
#include "nightswatch.h"
#include "jobs.h"
#include "kjob.h"
#include "overkill.h"
#include "fg.h"
#include "util.h"

void command_handler(char *curr_command){
    char *commarg[MA];
    ll totalcommarg = 0;
    tokenizer(commarg,curr_command," \t",&totalcommarg);

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

void redirecter(char *undirected){

    char *core_command;
    char *infile;
    char *outfile;

    core_command = strtok(undirected,">");
    outfile =strtok(NULL,"");                                       // contains >+file/file/NULL"
    core_command = strtok(core_command,"<");                        // contains file/NULL"
    infile = strtok(NULL,"");                                       // conatins file/NULL

    if(infile!=NULL){
        ll len =strlen(infile);

        ll i;
        for(i=0;i<len;i++){
            if(infile[i]!=' ' && infile[i]!='\t') break;
        }
        infile+=i;
        infile = strtok(infile," \t");
    }

    ll flag = 0;
    if(outfile!=NULL){
        if(outfile[0]=='>')flag = 1;  //append
        else flag = 0;  //overwrite

        ll len =strlen(outfile);
        ll i;
        for(i=0;i<len;i++){
            if(outfile[i]!='>' && outfile[i]!=' ') break;
        }
        outfile+=i;
        outfile = strtok(outfile," \t");
    }

    //printf("%s %s %s\n",core_command,infile,outfile);

    int actual_cin = dup(0);
    int actual_cout = dup(1);
    ll in=0,out=1;

    if(infile!=NULL){
        tilda_remover(infile);
        in = open(infile,O_RDONLY);
        if(in<0){
            tilda_adder(infile);
            perror(infile);
        }
    }
    if(outfile!=NULL){
        tilda_remover(outfile);
        if(flag==1) out=open(outfile,O_WRONLY|O_CREAT|O_APPEND,0644);
        else out=open(outfile,O_WRONLY|O_CREAT|O_TRUNC,0644);

        if(out<0){
            tilda_adder(outfile);
            perror(outfile);
        }
    }
    if(in < 0 || out < 0) return;
    dup2(in,STDIN_FILENO);
    dup2(out,STDOUT_FILENO);
    command_handler(core_command);

    if(in!=0)close(in);
    if(out!=1)close(out);

    dup2(actual_cin,STDIN_FILENO);
    dup2(actual_cout,STDOUT_FILENO);

}

void piper(char *pipe_command){
    char *unpiped_commands[MA];
    ll total_unpiped_commands = 0;
    tokenizer(unpiped_commands,pipe_command,"|",&total_unpiped_commands);

    int actual_cin = dup(0);
    int actual_cout = dup(1);

    int fd[2][2];

    for(ll i=0;i<total_unpiped_commands;i++){

        if(i==(total_unpiped_commands-1)){
            redirecter(unpiped_commands[i]);
            if(i!=0)close(fd[!(i%2)][0]);
        }
        else{
            if(pipe(fd[i%2]) == -1){
		        printf("Pipe creation makes an issue\n");
		        return;
	        }
            pid_t forkReturn = fork();
            if(forkReturn<0){
		        printf("Couldn't perform fork()\n");
		        return;
            }
            if(forkReturn==0){
                close(fd[i%2][0]);
                dup2(fd[i%2][1], 1);
		        redirecter(unpiped_commands[i]);

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
    ll totalcommands=0;
    tokenizer(allcommands,command,";\n",&totalcommands);

    for(ll task=0;task<totalcommands;task++){
        piper(allcommands[task]);
    }
}