#include <stdio.h>
#include <string.h>
#include "dbg.h"

#define MAX_DATA 10000

// TODO: change to read lines to remember line number
int findStr(char **target, FILE *fp)
{
    char **read_str = NULL;
    read_str = calloc(1, MAX_DATA);
    check_mem(read_str);

    while (fgets(*read_str, MAX_DATA, fp) != NULL) {
        if (strstr(*target, *read_str) != NULL) {
            free(*read_str);
            *read_str = NULL;
            return 1;
        } 
    }
    return -1;

error:
    // free the space pointed by read_str
	if (*read_str) free(*read_str);
    // free the space pointed by (**)target
	*read_str = NULL;
	return -1;
}

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        printf("You should enter a number.\n");
        goto error;
    }

    // TODO: how to take optional arguments like "-o"?
    // TODO: deal with or/and logic
    // TODO: Can fopen take string path var as parameter?
    // TODO: list all allowed log files from "~/.logfind"
    // TODO: list all allowed log files can be anything that the 'glob' function allows
    // TODO: output the matching lines as you can.

    char **currentStr = NULL;
    for (int i = 1; i<argc; i++) {
        // loads the list of allowed log files from ~/.logfind.
        FILE *fp = fopen("~/.logfind", "r"); 
    }
    return 0;

error:
    return -1;
}