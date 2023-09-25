#include "dbg.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// #define MAX_FILES 10
#define MAX_LINE_LENGTH 500

// TODO add `glob` functionality
int readLogFilePath(const char *logFileList, char ***fileList, int *count);
// TODO why use const char* is bad here?
int argparser(const int argc, const char* argv[], const int logicOr, char ***words, const int count);
int searchFiles(const char *FilePath, const char ***words, int NumWords, const int logicOr);

int main(int argc, char *argv[]) {
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-o") == 0)) {
        log_err("Nothing to find, please give keyword.");
    }

    int logicOr = (strcmp(argv[1], "-o") == 0)? 1 : 0;
    int count = argc - 1 - logicOr;
    int i;
    int rc;
    int fileCount;
    char ** fileList;
    char *logFileList = "./logfind";
    char **words = NULL;
    FILE *curFile;

    rc = readLogFilePath(logFileList, &fileList, &fileCount);
    check(rc != -1, "Failed to read %s", logFileList);
    rc = argparser(argc, argv, logicOr, &words, count);
    check(rc != -1, "Failed to read %s", logFileList);

    for (i = 0; i < fileCount; i++) {
        curFile = fopen(fileList[i], "r");
        check(curFile, "Failed to open %s.", fileList[i]);
        searchFiles(fileList[i], &words, count, logicOr);
        fclose(curFile);
    }

    // Free the memory allocated for search words
    for (i = 0; i < count; ++i) {
        free(words[i]);
    }
    free(words);

    // Free the memory allocated for each line
    for (i = 0; i < fileCount; i++) {
        free(fileList[i]);
    }
    // Free the memory allocated for the lines array
    free(fileList);
    return 0;

error:
    return -1;
}

int readLogFilePath(const char *logFileList, char ***fileList, int *count) {
    FILE *readLogFiles = fopen(logFileList, "r");
    check(readLogFiles, "Failed to open %s.", logFileList);

    // count the number of lines
    char ch;
    while((ch = fgetc(readLogFiles)) != EOF) {
        if(ch == '\n') {
            (*count)++;
        }
    }
    // Reset the file position to the beginning
    fseek(readLogFiles, 0, SEEK_SET);

    *fileList = (char **)malloc(*count * sizeof(char *));
    check(*fileList, "Failed to malloc");

    // save each line, dynamic decide their len
    char buffer[MAX_LINE_LENGTH];
    int i = 0;
    while(fgets(buffer, MAX_LINE_LENGTH, readLogFiles) != NULL) {
        (*fileList)[i] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy((*fileList[i]), buffer);
        ++i;
    }

    fclose(readLogFiles);

    return 0;

error:
    if (readLogFiles) fclose(readLogFiles);
    // 这里要不要return -1?好像外面函数重复输出了？
    return -1;
}

// TODO:pass by pointer not the whole value
int argparser(const int argc, const char* argv[], const int logicOr, char ***words, const int count) {
    int start = 1 + logicOr;
    int i;
    *words = (char**)malloc(count * sizeof(char*));
    check(*words, "malloc faield");
    for (i = 0; i < count; ++i) {
        (*words)[i] = (char *)malloc(strlen(argv[i+start]) * sizeof(char));
        check((*words)[i], "malloc failed");
        strcpy((*words)[i], argv[i+start]);
    }

error:
    return -1;
}

int searchFiles(const char *FilePath, const char ***words, int NumWords, const int logicOr) {
    FILE *file = fopen(FilePath, "r");
    check(file, "fopen failed");

    int lineCount = 0;
    int rc;
    char buffer[MAX_LINE_LENGTH];
    char *foundStr;
    int lineNum = 0;
    int i;
    // or logic
    if (logicOr == 1) {
        int finish = 0;
        while(fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
            for (i = 0; i < NumWords; ++i) {
                foundStr = strstr(buffer, (*words)[i]);
                if (foundStr != NULL) {
                    printf("Found %s in line %d, logic is OR, break", (*words)[i], lineNum);
                    finish = 1;
                    break;
                }
            }
            if(finish == 1) {
                break;
            }
            lineNum++;
        }

    // and logic
    } else if (logicOr == 0) {
        int *marker = (int *)malloc(sizeof(int) * NumWords);
        while((fgets(buffer, MAX_LINE_LENGTH, file)) != NULL) {
            for (i = 0; i < NumWords; ++i) {
                if (marker[i] != -1) {
                    continue;
                }
                foundStr = strstr(buffer, (*words)[i]);
                if (foundStr != NULL) {
                    marker[i] = lineNum;
                }
            }
            lineNum++;
        }
        for (i = 0; i < NumWords; ++i) {
            if (marker[i] == -1) {
                printf("Couldn't Found %s in file %s, logic is AND", (*words)[i], FilePath);
                break;
            }
        }
        printf("Found %s in file %s, line %d, logic is AND", (*words)[i], FilePath, marker[i]);
    } else {
        printf("Wrong Logic! \n");
    }


    fclose(file);

error:
    return -1;
}