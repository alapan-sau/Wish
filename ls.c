#include "main.h"
#include "util.h"


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

    char path[MA];

    for(ll i=1;i<n;i++){

        if(commarg[i][0]=='-')continue;
        totaldir--;
        strcpy(path,commarg[i]);

        tilda_remover(path);

        struct dirent *newfile;
        DIR *mydir = opendir(path);
        struct stat mystat;
        while((newfile = readdir(mydir)) != NULL){
            if(flag==4)printf("%s\n", newfile->d_name);
            else if(flag==0){
                if(newfile->d_name[0]!='.')printf("%s\n", newfile->d_name);
            }
            else{
                char buf[512];
                sprintf(buf, "%s/%s", path, newfile->d_name);
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