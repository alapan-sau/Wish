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
        char *address;
        address = malloc(100*sizeof(char));
        strcpy(address,homedir);
        strcat(address,path+1);
        strcpy(path,address);
    }
}

void tokenizer(char *token[],char *str,char *delim, ll *total){
    token[0] = strtok(str,delim);
    ll index = 0;
    while(token[index]!=NULL){
        token[++index] = strtok(NULL,delim);
    }
    *total = index;
}