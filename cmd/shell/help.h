/* This header lists the help for Quick Shell and all internal commands */
/* If you added a new command, put it in here */

#include <stdio.h>

#define CREDITS " "

#define VERSION_STAGE "alpha"
#define VERSION_NUM "0.0.4"
#define VERSION_STATUS "unstable"
#define REPO "(https://github.com/mckenney5/qsh)"

#define VERSION VERSION_STAGE " " VERSION_NUM " " VERSION_STATUS

void help();             // displays all help information
void command_args();     // list all command args and their uses
void commands();         // lists all internal commands and their uses
void default_aliases();  // lists all default internal command aliases

void help() {
    puts("qsh - a small, lightweight command interpreter");
    printf("Version: %s\n", VERSION);
    puts("======================================================");
    printf("The source code of this program is available here\n%s\n\n%s\n",
           REPO, CREDITS);
    puts("======================================================\n");
    puts("Command line args:");
    command_args();
    puts("\nInternal commands:");
    commands();
    puts("\nDefault aliases");
    default_aliases();
    puts(" ");
}

void command_args() {
    puts("\t--help\t\tThis stuff");
    puts("\t--run <cmd>\tRuns a command then exits");
}

void commands() {
    // list commands in alphabetical order
    // only internal commands should be noted in here
    // example: \tcls - clears the screen
    puts("\tcd\n\t\tChanges current directory");
    puts("\thelp\n\t\tDisplays this stuff");
    puts("\tquit\n\t\tQuits the program");
}

void default_aliases() {
    puts("\tNone.");
}
