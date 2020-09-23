#include "main.h"
#include "history.h"
#include "util.h"
#include "execute.h"
#include "overkill.h"
#include "signal_handlers.h"


void getcurdir(){                                       // stores the current dir to currdir
    if(getcwd(currdir,MA)==NULL){
        perror("");
        exit(0);
    }
    tilda_adder(currdir);
    return;
}

void getcommand(){                                          // fetches command from terminal
    size_t size_command = 100;

    command = (char *)malloc(size_command);
    if(command==NULL){
        fprintf(stderr,"Oops! Memory Error!\n");
    }
    int ctrld = getline(&command, &size_command, stdin);
    if(ctrld == -1){
        printf("\n");
        overkill();
        exit(0);
    }
}

void gethomedir(){                                             // stores home dir to homedir
    if(getcwd(homedir,MA)==NULL){
        perror("");
        exit(0);
    }

    return;
}

void reference(){                                                 // prompt function
    char emotion[MA];
    if(latest_status==1){
        strcpy(emotion,":')");
    }
    else{
        strcpy(emotion,":'(");
    }
    char username[MA];
    char hostname[MA];
    char reference[MA];
    getlogin_r(username,MA);                                          //fetches username
    gethostname(hostname,MA);                                         //fetches hostname
    getcurdir();
    sprintf(reference,"%s \033[0;91m<%s@%s:\033[0;93m%s\033[0;91m> \033[0m",emotion,username,hostname,currdir);
    printf("%s",reference);
}

int main(){
    latest_status=1;
    printf("\033[0;91m\n\n\t\t\t Welcome to C shell\n\n\033[0m");
    hisnum = 0;                                                    // total elements in historyarr
    jobtot=0;                                                      // total number of bg processes
    gethomedir();
    strcpy(prevdir,homedir);
    loadhistory();
    latest_fore_pid=-1;
    while(1){
        signal(SIGCHLD, sigchld_handler);                          // checks for any child termination signal
        signal(SIGINT,sigint_handler);
        signal(SIGTSTP,sigtstp_handler);
        reference();
        getcommand();
        if(updatehistory()==0){
            latest_status=0;
            continue;
        }
        latest_status=1;
        execute_command();
    }
}
