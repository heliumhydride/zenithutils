#include <stdio.h>            // fprintf(), getchar()
#include <string.h>           // strlen(), strtok(), strcpy()
#include <unistd.h>           // execvp(), fork()
#include <stdlib.h>           // malloc()
#include "../include/util.h"  // da_append(), da_destroy(), print_error()
#include "../config.h"        // STDIN_MAX

#ifndef _WIN32 // On Unix
#include <sys/wait.h>         // waitpid(), WIFEXITED, WEXITSTATUS
#endif // !_WIN32

typedef struct {
    char   **data;
    size_t count;
    size_t capacity;
} da_args;

// TODO -0 option
void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s command\n", program);
}

int main(int argc, char* argv[])
{
    const char* program = argv[0];
    shift_args(&argc, &argv);

    // TODO --help
    if(argc == 0) {
        print_usage(program);
        return 1;
    }

    char* path = *argv;
    char buf[STDIN_MAX] = {0};
    int c;
    int i = 0;
    while((c = getchar()) != EOF) {
        buf[i] = (char)c;
        i++;
    }
    buf[i] = '\0';

    // start building new argv from the program's one (after the program path)
    da_args new_argv = {0};
    da_append(&new_argv, path);
    while(*++argv) da_append(&new_argv, *argv);

    // build the rest of new argv from buffer (stdin)
    const char* separators = " \n\t";
    char* pch = strtok(buf, separators);
    while(pch != NULL) {
        char* pch2 = malloc(strlen(pch) + 1);
        if(pch2 == NULL) {
            print_error("%s: malloc() failed", program);
            return 2;
        }
        strcpy(pch2, pch);
        da_append(&new_argv, pch2);
        pch = strtok(NULL, separators);
    }
    da_append(&new_argv, NULL);

    int res = 126;
    #ifdef _WIN32
    res = execvp(path, new_argv.data);
    #else // On Unix
    int wstatus;
    pid_t pid = fork();
    switch(pid) {
        case -1:
            print_error("%s: could not fork()", program);
            return 2;
        case 0:
            res = execvp(path, new_argv.data);
            break;
        default:
            (void)waitpid(pid, &wstatus, 0);
            if(WIFEXITED(wstatus))
                res = WEXITSTATUS(wstatus);
            break;
    }
    #endif // _WIN32

    da_destroy(&new_argv);
    return res;
}

