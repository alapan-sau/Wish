#include "main.h"

void cd(char *path){                                                            // cd
    char address[MA];
    if(path[0]=='~'){
    strcpy(address,homedir);
    strcat(address,path+1);
    }
    else strcpy(address,path);
    chdir(address);
    getcurdir();
}