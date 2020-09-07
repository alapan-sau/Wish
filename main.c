#include "main.h"
#include "history.h"
#include "util.h"
#include "execute.h"
#include "sigchld_handler.h"


void getcurdir(){                                               // stores the current dir to currdir
    if(getcwd(currdir,MA)==NULL){
        perror("");
        exit(0);
    }
    tilda_adder(currdir);
    return;
}

void getcommand(){                                                  // fetches command from terminal
    size_t size_command = 100;

    command = (char *)malloc(size_command);
    if(command==NULL){
        printf("Oops! Memory Error!\n");
    }
    getline(&command, &size_command, stdin);
}

void gethomedir(){                                                  // stores home dir to homedir
    if(getcwd(homedir,MA)==NULL){
        perror("");
        exit(0);
    }

    return;
}

void reference(){                                                    // prompt fx
    char username[MA];
    char hostname[MA];
    char reference[MA];
    getlogin_r(username,MA);
    gethostname(hostname,MA);
    getcurdir();
    sprintf(reference,"\033[0;91m<%s@%s:\033[0;93m%s\033[0;91m> \033[0m",username,hostname,currdir);
    printf("%s",reference);
}

int main(){
    hisnum = 0;
    jobtot=0;
    gethomedir();
    loadhistory();
    while(1){
        signal(SIGCHLD, sigchld_handler);
        reference();
        getcommand();
        updatehistory();
        execute_command();
    }
}