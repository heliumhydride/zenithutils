#define  _XOPEN_SOURCE 500     // lstat(), strdup()
#include <stdio.h>             // fprintf(), printf(), putchar()
#include <stdlib.h>            // qsort(), free()
#include <sys/stat.h>          // lstat(), struct stat
#include <dirent.h>            // opendir(), closedir(), readdir()
#include <errno.h>             // E* constants (ENOTDIR, ENOENT, EACCES)
#include <unistd.h>            // access()
#include <string.h>            // strcmp(), strcat(), strcpy(), strdup()
#include <getopt.h>            // getopt(), optind, optopt
#include "../include/util.h"   // print_error(), file_ext_is(), perror2(), shift_args(), da_append(), da_destroy(), da_reverse()
#include "../include/colors.h" // ANSI_*
#include "../config.h"         // LSCOLOR, PATHNAME_MAX, FORCE_MINGW_PATHS

#ifdef _WIN32
// #define S_IFMT   0xf000
#define S_IFSOCK 0xc000 // TODO likely immensely wrong and not defind for a reason, but
#define S_IFLNK  0xa000 //      avoids compilation errors [1]
// #define S_IFREG  0x8000
// #define S_IFBLK  0x6000
// #define S_IFDIR  0x4000
// #define S_IFCHR  0x2000
// #define S_IFIFO  0x1000
#define lstat stat
#endif // _WIN32

// TODO options (-laA)
// TODO print individual files, with color
// TODO show directory names if there are multiple directories
// TODO formatting
// TODO color tarballs
// TODO LS_COLORS env variable

#ifdef _WIN32
#define file_is_executable(f) str_endswith((f), ".exe") || \
                              str_endswith((f), ".cmd") || \
                              str_endswith((f), ".bat") // TODO this configuration is not hardcoded into windows
#else // On Unix
#define file_is_executable(f) access((f), X_OK) == 0
#endif // _WIN32

static char *program;
static int oneflag;
// static int Aflag;
// static int aflag;
// static int lflag;
static int rflag;
static int sort_type;

enum {
    SORT_APLHA, // default
    SORT_TIME,  // -t
    SORT_SIZE,  // -S
};

typedef struct {
    char        *filename;
    struct stat st;
} fileinfo_t;

typedef struct {
    fileinfo_t *data;
    size_t     count;
    size_t     capacity;
} da_fileinfo;

int compare_byname(const void *a, const void *b)
{
    return strcmp(((fileinfo_t*)a)->filename, ((fileinfo_t*)b)->filename);
}

int compare_bytime(const void *a, const void *b)
{
    // TODO incorrect sorting ?
    time_t t1 = ((const fileinfo_t*)a)->st.st_mtime;
    time_t t2 = ((const fileinfo_t*)b)->st.st_mtime;
    if(t1 > t2)  return -1;
    if(t1 < t2)  return 1;
    return 0;
}

int compare_bysize(const void *a, const void *b)
{
    off_t s1 = ((const fileinfo_t*)a)->st.st_size;
    off_t s2 = ((const fileinfo_t*)b)->st.st_size;
    if(s1 > s2)  return -1;
    if(s1 < s2)  return 1;
    return 0;
}

int ls(char *path)
{
    // char type = 'd';
    struct dirent* ent;
    DIR* d = opendir(path);
    if(!d) {
        if(errno == ENOTDIR) {
            // type = 'f';
            __TODO("ls for single files");
        } else {
            char errstring[150] = {0};
            snprintf(errstring, sizeof(errstring), "could not access '%s'", path);
            perror2(errstring, program);
            return 1;
        }
    }

    // build list of fileinfos
    da_fileinfo fileinfos = {0};
    struct stat sb;
    while((ent = readdir(d))) {
        // concat current dir to filename
        char *dirpath  = strdup(ent->d_name);
        char filepath[PATHNAME_MAX] = {0};
        strcpy(filepath, path);
        strcat(filepath, "/");
        strcat(filepath, dirpath);

        if(lstat(filepath, &sb) == -1) {
            char errstring[150] = {0};
            snprintf(errstring, sizeof(errstring), "could not stat '%s'", filepath);
            perror2(errstring, program);
        }
        fileinfo_t fi = {dirpath, sb};
        da_append(&fileinfos, fi);
    }

    // sort them
    int (*compare)(const void*, const void*) = NULL;
    switch(sort_type) {
        case SORT_APLHA:
            compare = &compare_byname;
            break;
        case SORT_TIME:
            compare = &compare_bytime;
            break;
        case SORT_SIZE:
            compare = &compare_bysize;
            break;
    }
    qsort(fileinfos.data, fileinfos.count, sizeof(fileinfo_t), compare);
    if(rflag)  da_reverse(&fileinfos, fileinfo_t);

    for(size_t i = 0; i < fileinfos.count; ++i) {
        fileinfo_t fi = fileinfos.data[i];
#if LS_COLOR
        mode_t filetype = fi.st.st_mode & S_IFMT;
        if(file_is_executable(fi.filename))
            printf(ANSI_GREEN);
        // ^^^ TODO should probably be done using stat
        switch(filetype) {
            case S_IFDIR:
                printf(ANSI_BLUE);
                break;
            case S_IFLNK: // [1]
                printf(ANSI_CYAN);
                break;
            case S_IFCHR:
            case S_IFBLK:
                printf(ANSI_YELLOW);
                break;
            case S_IFIFO:
            case S_IFSOCK: // [1]
                printf(ANSI_MAGENTA);
                break;
        }
#endif
        // TODO -A, -a, -l
        printf("%s  ", fi.filename);
        if(oneflag) putchar('\n');
        else      printf("  ");   // TODO formatting
#if LS_COLOR
        printf(ANSI_NORM);
#endif
    }

    // if(type == 'd') closedir(d);
    closedir(d);
    for(size_t i = 0; i < fileinfos.count; ++i)
        free(fileinfos.data[i].filename);
    da_destroy(&fileinfos);
    return 0;
}

void print_usage(const char *program)
{
    // TODO !!! if opts are updated, update them here !!!
    fprintf(stderr, "usage: %s [-AalrSt]\n", program);
}

int main(int argc, char* argv[])
{
    program = argv[0];

    if(argc >= 2 && !strcmp(argv[1], "--help")) {
        print_usage(program);
        return 0;
    }

    oneflag = 0;
    // aflag = 0;
    // Aflag = 0;
    // lflag = 0;
    rflag = 0;
    sort_type = SORT_APLHA;

    int opt;
    while((opt = getopt(argc, argv, ":1AalrSt")) != -1) {
        switch(opt) {
            case '1':
                oneflag = 1;
                break;
            /*
            case 'A':
                Aflag = 1;
                break;
            case 'a':
                aflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            */
            case 'r':
                rflag = 1;
                break;
            case 'S':
                sort_type = SORT_SIZE;
                break;
            case 't':
                sort_type = SORT_TIME;
                break;
            case '?':
                print_error("%s: invalid option -- '%c'", program, optopt);
                print_usage(program);
                return 1;
                break;
        }
    }
    shift_args_n(&argc, &argv, optind);

    if(argc == 0) {
        --argv;
        ++argc;
        *argv = ".";
    }

    while(*argv) {
        if(ls(*argv))  return 1;
        if(!oneflag)   putchar('\n');
        shift_args(&argc, &argv);
    }

    return 0;
}
