/**
 * @file logfind.c
 * @author gaaoyi@gmail.com)
 * @brief Find all occurrence of passed arg in ./ex26 folder 
 * @version 0.1
 * @date 2023-05-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include "dbg.h"

#define MAX_DATA 1000
#define MAX_LINE 100
#define MAX_FIND 200


// TODO: haddle found to not pass MAX_FIND
// TODO: actually don't need to using 2-d array pointer, just use print in this function will be fine
void find_all_occurrences(char *str1, char *str2, int **store, const int *line_number, int *found) {
    char *ptr = str1;
    int index;

    while (ptr != NULL) {
        ptr = strstr(ptr, str2);
        if (ptr != NULL) {
            index = ptr - str1;  // Calculate the index
            store[*found] = (int*)malloc(sizeof(int) * 2);
            store[*found][0] = *line_number;
            store[*found][1] = index;
            *found += 1;
            printf("Found at index: %d\n", index);
            ptr += strlen(str2);  // Move past the last match
        }
    }
}

int strEndWith(const char *str1, const char *str2) {
    // Get the length of the strings
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Check if str1 ends with str2
    if (len1 >= len2 && strcmp(str1 + len1 - len2, str2) == 0) {
        return 1;
    } else {
        return 0;
    }
}
// Assuming a line is never longer than MAX_DATA
// return a array of founded line
// DONE: Handle EOF of fgets
// DONE: return 2-d array pointer to save line number and pos of line
// TODO: compare to author's scan_file, should do better naming
// TODO: should return int **, even though no error
int *findStr(const char *target, const char* file)
{
    FILE *curFP = fopen(file, "r");
    check(curFP != NULL, "open file %s failed", file);

    // TODO even though here store should be int ** but no error?
    int *store = (int**)malloc(sizeof(int*) * MAX_FIND);
    for (int i = 0; i < MAX_FIND; i++) {
        store[i] = NULL;
    }

    check_mem(store);
    char *read_str = calloc(1, MAX_DATA);
    check_mem(read_str);
    
    int line_num = 1;
    int found = 0;
    
    while (line_num <= MAX_LINE && found < MAX_FIND) {
        char *res = fgets(read_str, MAX_DATA, curFP);
        if (res == NULL) {
            if (!feof(curFP)) {
                printf("error when fgets() read files %s\n", file);
                printf("\n");
                goto error;
            }
        }
        
        find_all_occurrences(read_str, target, store, &line_num, &found);
        memset(read_str, 0, MAX_DATA);
        line_num += 1;
    }
    // DONE: stack memory can not be return
    fclose(curFP);
    if (found == 0) {
        return NULL;
    }
    return store;

error:
    free(store);
    // free the space pointed by read_str
	if (read_str) free(read_str);
    if (curFP) fclose(curFP);
	return NULL;
}

// TODO: only glob pattern saved in .logfind
// TODO: when do this, you need to trim the '/n' added by fgets()
int listFiles(char* logfindDir, glob_t *pglob) {
    
    int i = 0;
    // check if logfindDir is end with "/"
    char *pattern = NULL;
    if (strEndWith(logfindDir, "/")) {
        pattern = calloc(1, strlen(logfindDir)+1);
        check_mem(pattern);
        strcpy(pattern, logfindDir);
    } else {
        pattern = calloc(1, strlen(logfindDir) + 2);
        check_mem(pattern);
        strcpy(pattern, logfindDir);
        strcat(pattern, "/");
    }

    check(pglob != NULL, "Invalid glob_t given.");

    // TODO: read about GLOB flags, GLOB_TILDE and GLOB_APPEND
    int glob_flags = GLOB_TILDE;
    int rc = glob(strcat(pattern, "*"), glob_flags, NULL, pglob);
    check(rc == 0 || rc == GLOB_NOMATCH, "glob error");
    
    for(i = 0; i < pglob->gl_pathc; i++) {
        debug("Matched file: %s", pglob->gl_pathv[i]);
    }
    
    free(pattern);
    return 0;
    
error:
    return -1;
}

int main(int argc, char *argv[])
{
    // DONE: 2-dim array and initialize?
    int founds[argc-1][MAX_FIND];
    for (int i = 0; i < argc - 1; i++) {
        memset(founds[i], 0, sizeof(founds[i]));
    }
    
    if (argc <= 1 || (argc == 2 && strcmp(argv[1], "-o") == 0)) {
        printf("You should enter the strings you want to search.\n");
        goto error;
    }
    
    int or = 0;
    if (strcmp(argv[1], "-o") == 0) {// check if "-o" is present
        or = 1;
    }
    
    // TODO: find all occurrence not just once, and log the postion of the matching line
    // TODO: Do not need to initialize glob_t, this will be done by glob()
    glob_t pglob;
    // read allowed files from ex26 folder
    listFiles("/Users/yigao/Developer/learn_C_the_hard_way/ex26", &pglob);
    for (int i = 1 + or; i<argc; i++) {
        // loads the list of allowed log files from ~/.logfind.
        // what happens if not initialized?
        for (int j = 0; j < pglob.gl_pathc; j++) {
            char *curFile = pglob.gl_pathv[j];
            int **lines = findStr(argv[i], curFile);
            if (lines == NULL) {
                continue;
            }
            // TODO: what does sizeof() return if parameter is allocated by malloc but not fully used?
            for (int k = 0; k < MAX_FIND && lines[k] != NULL; k++) {
                printf("Found %s on lien %d,%d of file %s\n\n", argv[i], lines[k][0], lines[k][1], pglob.gl_pathv[j]);
                free(lines[k]);
            }
            free(lines);
        }
    }
    return 0;

error:
    return -1;
}