# C Shell

## This is a BASH like shell written in C for Linux. <br> <br>

## How to Use?

1. Run `make` in the Shell directory to compile the C Shell.
2. Run `./main` to execute the shell.

<br>

## Commands

1. `echo [string]` <br>
    * Implemented in echo.c
    * Takes a string argument and prints it back after removing extra spaces and puts a newline at the end. No arguments means null string.

2. `pwd` <br>
    * Implemented in pwd.c
    * Prints the current working directory of the shell

3. `cd` [Location] <br>
    * Implemented in cd.c
    * Takes a path to a directory as an input and makes it the current working directory. With no arguments, it makes `~` as the current working directory.

4. `ls [-l -a -al -la] [Directory]` <br>
    * Implemented in ls.c
    * Lists all the files and directories in the mentioned directory/directories. If no parameters are passed, lists the contents of current directory.
    * The `-l` flag lists the contents in a more descriptive way by providing some information about each item.
    * The `-a` flag is used to include the hidden files and folders in the listing.

5. `pinfo [Process ID]` <br>
    * Implemented in pinfo.c
    * Takes a process ID as input and provides information about the process.
    * With no arguments it provides information about the shell process running.

6. `history [number]` <br>
    * Implemented in history.c
    * Takes a `number` as an input and lists the last number of valid/invalid commands executed. Continuas repetitions are avoided.
    * With no arguments it prints the last `10` such commands.

7. `nightswatch -n [seconds] [interrupts|newborn]` <br>
    * Implemented in nightswatch.c
    * Interrupts prints the total number of keyboard interrupts.
    * Newborn prints the Process ID of newest process.
    * Commands are executed every `seconds` secs interval.
    * Press `q + Enter` to stop the execution.

9. `quit`
    * Quits the C Shell.
    * This will kill all background and foreground processes run on the Shell.

## Note
1. Any command with `&` as the last character will be treated as a background process. Any controlling terminal process will be suspended.