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

void starter(){
    char username[MA];
    char hostname[MA];
    char reference[MA];
    getlogin_r(username,MA);                                          //fetches username
    gethostname(hostname,MA);                                         //fetches hostname
    username[0] = (char)toupper(username[0]);
    fprintf(stderr,clear);
    fprintf(stderr,BHRED);
    fprintf(stderr,"\nHello %s! Nice to meet you! \n",username);
    fprintf(stderr,"\nI am ASH, your new shell\nI am designed by Alapan\nPlease report any shit I do to him :) Dont worry, its not a complaint, just a help in diagnosis for my treatment\n");
    fprintf(stderr,"alapan.sau@students.iiit.ac.in\n\n");
    fprintf(stderr,reset);
}