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
        printf("Oops! Memory Error!\n");
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

void reference(){                                                     // prompt function
    char username[MA];
    char hostname[MA];
    char reference[MA];
    getlogin_r(username,MA);                                          //fetches username
    gethostname(hostname,MA);                                         //fetches hostname
    getcurdir();
    sprintf(reference,"\033[0;91m<%s@%s:\033[0;93m%s\033[0;91m> \033[0m",username,hostname,currdir);
    printf("%s",reference);
}

int main(){

    printf("\033[0;91m\n\n\t\t\t Welcome to C shell\n\n");
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
        updatehistory();
        execute_command();
    }
}
