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

char historyarr[20][100];
ll hisnum;

ll jobtot;
ll jobindex[MA];
char *jobs[MA];


void getcurdir();
void execute_command();
void getcommand();
void gethomedir();
void reference();