#include "main.h"
#include "util.h"

void cd(char *path){                                                            // cd
    tilda_remover(path);
    chdir(path);
    getcurdir();
}