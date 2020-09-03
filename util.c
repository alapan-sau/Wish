#include "main.h"

void tilda_adder(char *path){
    ll lenHome = strlen(homedir);
    ll lenPath = strlen(path);

    if(lenHome > lenPath) return;
    for(ll i=0;i<lenHome;i++){
        if(homedir[i]!=path[i]) return;
    }

    char address[MA];
    strcpy(address,"~");
    strcat(address,path+lenHome);
    strcpy(path,address);
}

void tilda_remover(char *path){
    if(path[0]=='~'){
        char address[MA];
        strcpy(address,homedir);
        strcat(address,path+1);
        strcpy(path,address);
    }
}