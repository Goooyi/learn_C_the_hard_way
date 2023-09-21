#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int readLogFilePath(char ** fileList, int *count) {
    char **logFiles = "~/.logfind";
    FILE *curFile = NULL;
    curFile = open(logFiles, "r");
    check(curFile, "Failed to open %s.", file_name);
    // How to read lines from fopend files?
    fclose(curFile);
    curFile = NULL;

    return 0;

error:
    if (curFile) fclose(curFile);
    // 这里要不要return -1?好像外面函数重复输出了？
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc == 1 || (argc == 2 && argv[1] == "-o")) {
        log_err("Nothing to find, please give keyword.")
    }

    int logic = (argv[1] == "-o")? 1 : 0;

    // TODO: scan all dir for LOG?
    int i;
    int *fileCount;
    char ** fileList;

    int rc = readLogFilePath(fileList, fileCount)

    for (i = 0; i < fileCount; i++) {
        curFile = fopen(fileList[i], 'r');
        check(curFile, "Failed to open %s.", file_name);
        // TODO: how to do search? golb!!!
    }

error:
    return -1;
}