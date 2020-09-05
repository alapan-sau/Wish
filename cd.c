#include "main.h"
#include "util.h"

void cd(ll n,char *commarg[]){                                                            // cd
    if(n > 2){
        printf("cd : too many arguments!\n");
        return;
    }
    else if(n==1){
        if(chdir(homedir)<0){
            perror("cd ");
        }
    }
    else {
        tilda_remover(commarg[1]);
        if(chdir(commarg[1])<0){
            perror("cd ");
        }
    }
    getcurdir();
}