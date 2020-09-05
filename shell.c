#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>

#define ll long long int
#define MA 100000


char homedir[MA];
char currdir[MA];

char *command;

void history(char *command){

}

void sigchld_handler(int signum)                                                // signal Handler
{
    pid_t pid;
    int   status;
    // while ((pid = waitpid(-1, &status, WNOHANG)) != -1)
    // {
    //     printf("%d ended\n",pid);   // Or whatever you need to do with the PID
    // }
    pid = waitpid(-1, &status, WNOHANG);
    if(pid!=-1)printf("%d ended\n",pid);
}


void getcurdir(){                                                           // stores the current dir to currdir
    getcwd(currdir,MA);
    if(strcmp(currdir,homedir)==0) strcpy(currdir,"~");
    else{
        ll len = strlen(homedir);
        ll index=0;
        for(index=0;index<len;index++){
            if(homedir[index]!=currdir[index])
                return;
        }
        ll i=1;
        len = strlen(currdir);
        for(;index<=len;index++,i++)
            currdir[i]=currdir[index];
        currdir[0]='~';
    }
    return;
}

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

void ls(ll n, char *commarg[]){                                                 // ls -l -la -a ...

    ll flagArg=0;
    ll flagA=0;
    ll flagL=0;

    ll totaldir = 0;
    for(ll i=1;i<n;i++){
        if(commarg[i][0]=='-'){
            if(strcmp(commarg[i],"-l")==0){
                flagL=1;
            }
            if(strcmp(commarg[i],"-a")==0){
                flagA=1;
            }
            if(strcmp(commarg[i],"-la")==0){
                flagL=1;
                flagA=1;
            }
            if(strcmp(commarg[i],"-al")==0){
                flagL=1;
                flagA=1;
            }
        }
        else{
            flagArg=1;
            totaldir++;
        }
    }
    ll flag = 0;                                                        // normal ls=0, ls -l=1, ls -la=2, ls -a=4,
    if(flagA && flagL) flag = 2;
    else if(flagA) flag = 4;
    else if(flagL) flag = 1;
    else flag = 0;

    if(flagArg==0){
        commarg[n]=currdir;
        n++;
        totaldir++;
    }

    char * path;
    for(ll i=1;i<n;i++){
        if(commarg[i][0]=='-')continue;
        totaldir--;
        path = commarg[i];
        char address[MA];
        if(path[0]=='~'){
            strcpy(address,homedir);
            strcat(address,path+1);
        }
        else strcpy(address,path);


        struct dirent *newfile;
        DIR *mydir = opendir(address);
        struct stat mystat;
        while((newfile = readdir(mydir)) != NULL){
            if(flag==4)printf("%s\n", newfile->d_name);
            else if(flag==0){
                if(newfile->d_name[0]!='.')printf("%s\n", newfile->d_name);
            }
            else{
                char buf[512];
                sprintf(buf, "%s/%s", address, newfile->d_name);
                if(stat(buf, &mystat) < 0)
                    return;
                char permissions[20];
                strcpy(permissions,"");
                strcat(permissions,(S_ISDIR(mystat.st_mode)) ? "d" : "-");
                strcat(permissions,(mystat.st_mode & S_IRUSR) ? "r" : "-");
                strcat(permissions,(mystat.st_mode & S_IWUSR) ? "w" : "-");
                strcat(permissions,(mystat.st_mode & S_IXUSR) ? "x" : "-");
                strcat(permissions,(mystat.st_mode & S_IRGRP) ? "r" : "-");
                strcat(permissions,(mystat.st_mode & S_IWGRP) ? "w" : "-");
                strcat(permissions,(mystat.st_mode & S_IXGRP) ? "x" : "-");
                strcat(permissions,(mystat.st_mode & S_IROTH) ? "r" : "-");
                strcat(permissions,(mystat.st_mode & S_IWOTH) ? "w" : "-");
                strcat(permissions,(mystat.st_mode & S_IXOTH) ? "x" : "-");

                char format[500];
                struct passwd *pw = getpwuid(mystat.st_uid);
                struct group  *gr = getgrgid(mystat.st_gid);
                char date[20];
                strftime(date, 20, "%b  %d  %I:%M", gmtime(&(mystat.st_ctime)));
                sprintf(format,"%s %10d %10s  %10s  %10d  %10s  %s\n",permissions, (int)mystat.st_nlink, pw->pw_name, gr->gr_name, (int)mystat.st_size, date, newfile->d_name);
                if(flag == 2) printf("%s",format);
                else if(flag ==1){
                    if(newfile->d_name[0]!='.')printf("%s",format);
                }
            }
        }
        closedir(mydir);
        if(totaldir) printf("\n");
    }
}

void backProcess(ll n, char *commarg[]){
    ll forkReturn = fork();
    if(forkReturn==0){                                                // background/child process
        commarg[n-1]=NULL;
        execvp(commarg[0],commarg);
        exit(0);
    }
    else{
        printf("%d started\n",getpid());
        return;
    }
}

void foreProcess(ll n,char *commarg[]){
    ll forkReturn = fork();
    if(forkReturn==0){                                                // foreground/child process
        commarg[n]=NULL;
        execvp(commarg[0],commarg);
        exit(0);
    }
    else{
        wait(NULL);
        return;
    }
}

void pinfo(ll n, char *commarg[]){                                      // pinfo
    pid_t pid;
    if(n==1) pid = getpid();
    else pid = atoi(commarg[1]);
    char procfile[1000];
    char execfile[1000];
    sprintf(procfile, "/proc/%d/stat", pid);
    sprintf(execfile, "/proc/%d/exe", pid);

    char status;
    ll memory;
    FILE  *procfd = fopen(procfile, "r");
    fscanf(procfd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lld %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status, &memory);
    fclose(procfd);
    printf("PID -- %d\n", pid);
    printf("Process Status -- %c\n", status);
    printf("Memory -- %lld\n", memory);

    char procadd[MA];
    int len = readlink(execfile, procadd, sizeof(procadd));
    procadd[len] = '\0';

    len = strlen(homedir);
    ll index=0;
    for(index=0;index<len;index++){
        if(homedir[index]!=procadd[index]){
            printf("Executable Path --  %s\n", procadd);
            return;
        }
    }
    char address[MA];
    strcpy(address,"~");
    strcat(address,procadd+strlen(homedir));
    printf("Executable Path --  %s\n", address);
}

void execute_command(){                                                 // command handler

    char *allcommands[MA];
    allcommands[0] = strtok(command,";\n");
    ll index = 0;
    while(allcommands[index]!=NULL){
        allcommands[++index] = strtok(NULL,";\n");
    }
    ll totalcommands = index;

    for(ll task=0;task<totalcommands;task++){
        char *commarg[MA];
        commarg[0] = strtok(allcommands[task]," ");
        index = 0;
        while(commarg[index]!=NULL){
            commarg[++index] = strtok(NULL," ");
        }
        ll totalcommarg = index;

        if(strcmp(commarg[totalcommarg-1],"&")==0){
            backProcess(totalcommarg,commarg);
            continue;
        }
        if(strcmp(commarg[0],"cd")==0){
            if(totalcommarg==1) cd("~");
            else cd(commarg[1]);
        }
        else if(strcmp(commarg[0],"mkdir")==0){
            mkdir(commarg[1],0777);
        }
        else if(strcmp(commarg[0],"pwd")==0){
            getcurdir();
            printf("%s\n",currdir);
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
        else if(strcmp(commarg[0],"q")==0){
            exit(0);
        }
        else if(strcmp(commarg[0],"pinfo")==0){
            pinfo(totalcommarg,commarg);
        }
        else{
            foreProcess(totalcommarg,commarg);
            continue;
        }
    }
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
    getcwd(homedir,MA);
    return;
}

void reference(){                                                    // prompt fx
    char username[MA];
    char hostname[MA];
    char reference[MA];
    getlogin_r(username,MA);
    gethostname(hostname,MA);
    getcurdir();
    sprintf(reference,"\033[0;91m<%s@%s:\033[0;93m%s\033[0;91m> \033[0;97m",username,hostname,currdir);
    printf("%s",reference);
}

int main(){
    gethomedir();
    while(1){
        signal(SIGCHLD, sigchld_handler);
        reference();
        getcommand();
        execute_command();
    }
}