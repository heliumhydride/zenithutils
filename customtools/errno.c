#include <errno.h>            // hmm... i wonder why
#include <stdio.h>            // printf() et al.
#include <stdlib.h>           // strtol()
#include <string.h>           // strcmp()
#include <unistd.h>           // ssize_t
#include "../include/util.h"  // print_error(), shift_args()

/*
    TODOS
        TODO write manpage errno(1) documentation
        TODO searching errors by string, (errno -s permission)
*/

typedef struct {
    const char *error_name;
    int error_no;
} error;

const error errmap[] = {
    {"EPERM", 1},             {"ENOENT", 2},            {"ESRCH", 3},         {"EINTR", 4},
    {"EIO", 5},               {"ENXIO", 6},             {"E2BIG", 7},         {"ENOEXEC", 8},
    {"EBADF", 9},             {"ECHILD", 10},           {"EAGAIN", 11},       {"ENOMEM", 12},
    {"EACCES", 13},           {"EFAULT", 14},           {"ENOTBLK", 15},      {"EBUSY", 16},
    {"EEXIST", 17},           {"EXDEV", 18},            {"ENODEV", 19},       {"ENOTDIR", 20},
    {"EISDIR", 21},           {"EINVAL", 22},           {"ENFILE", 23},       {"EMFILE", 24},
    {"ENOTTY", 25},           {"ETXTBSY", 26},          {"EFBIG", 27},        {"ENOSPC", 28},
    {"ESPIPE", 29},           {"EROFS", 30},            {"EMLINK", 31},       {"EPIPE", 32},
    {"EDOM", 33},             {"ERANGE", 34},           {"EDEADLK", 35},      {"ENAMETOOLONG", 36},
    {"ENOLCK", 37},           {"ENOSYS", 38},           {"ENOTEMPTY", 39},    {"ELOOP", 40},
    {"EWOULDBLOCK", EAGAIN},  {"ENOMSG", 42},           {"EIDRM", 43},        {"ECHRNG", 44},
    {"EL2NSYNC", 45},         {"EL3HLT", 46},           {"EL3RST", 47},       {"ELNRNG", 48},
    {"EUNATCH", 49},          {"ENOCSI", 50},           {"EL2HLT", 51},       {"EBADE", 52},
    {"EBADR", 53},            {"EXFULL", 54},           {"ENOANO", 55},       {"EBADRQC", 56},
    {"EBADSLT", 57},          {"EDEADLOCK", EDEADLK},   {"EBFONT", 59},       {"ENOSTR", 60},
    {"ENODATA", 61},          {"ETIME", 62},            {"ENOSR", 63},        {"ENONET", 64},
    {"ENOPKG", 65},           {"EREMOTE", 66},          {"ENOLINK", 67},      {"EADV", 68},
    {"ESRMNT", 69},           {"ECOMM", 70},            {"EPROTO", 71},       {"EMULTIHOP", 72},
    {"EDOTDOT", 73},          {"EBADMSG", 74},          {"EOVERFLOW", 75},    {"ENOTUNIQ", 76},
    {"EBADFD", 77},           {"EREMCHG", 78},          {"ELIBACC", 79},      {"ELIBBAD", 80},
    {"ELIBSCN", 81},          {"ELIBMAX", 82},          {"ELIBEXEC", 83},     {"EILSEQ", 84},
    {"ERESTART", 85},         {"ESTRPIPE", 86},         {"EUSERS", 87},       {"ENOTSOCK", 88},
    {"EDESTADDRREQ", 89},     {"EMSGSIZE", 90},         {"EPROTOTYPE", 91},   {"ENOPROTOOPT", 92},
    {"EPROTONOSUPPORT", 93},  {"ESOCKTNOSUPPORT", 94},  {"EOPNOTSUPP", 95},   {"ENOTSUP", EOPNOTSUPP},
    {"EPFNOSUPPORT", 96},     {"EAFNOSUPPORT", 97},     {"EADDRINUSE", 98},   {"EADDRNOTAVAIL", 99},
    {"ENETDOWN", 100},        {"ENETUNREACH", 101},     {"ENETRESET", 102},   {"ECONNABORTED", 103},
    {"ECONNRESET", 104},      {"ENOBUFS", 105},         {"EISCONN", 106},     {"ENOTCONN", 107},
    {"ESHUTDOWN", 108},       {"ETOOMANYREFS", 109},    {"ETIMEDOUT", 110},   {"ECONNREFUSED", 111},
    {"EHOSTDOWN", 112},       {"EHOSTUNREACH", 113},    {"EALREADY", 114},    {"EINPROGRESS", 115},
    {"ESTALE", 116},          {"EUCLEAN", 117},         {"ENOTNAM", 118},     {"ENAVAIL", 119},
    {"EISNAM", 120},          {"EREMOTEIO", 121},       {"EDQUOT", 122},      {"ENOMEDIUM", 123},
    {"EMEDIUMTYPE", 124},     {"ECANCELED", 125},       {"ENOKEY", 126},      {"EKEYEXPIRED", 127},
    {"EKEYREVOKED", 128},     {"EKEYREJECTED", 129},    {"EOWNERDEAD", 130},  {"ENOTRECOVERABLE", 131},
    {"ERFKILL", 132},         {"EHWPOISON", 133}
};

#define ERRMAP_SIZE (sizeof(errmap)/sizeof(error))

ssize_t lookup_error_byname(const char *errname)
{
    for(size_t i = 0; i < ERRMAP_SIZE; ++i) {
        if(strcmp(errmap[i].error_name, errname) == 0)
            return (ssize_t)i;
    }
    return -1;
}

void print_usage(const char *program)
{
    fprintf(stderr, "usage:    %s [err number]\n", program);
    fprintf(stderr, "          %s [err name]\n", program);
    fprintf(stderr, "          %s -l\n\n", program);
    fprintf(stderr, "examples: %s ENOTDIR\n", program);
    fprintf(stderr, "          %s 10\n", program);
}

int main(int argc, char *argv[])
{
    const char *program = argv[0];
    if(argc <= 1) {
        print_usage(program);
        return 1;
    }

    shift_args(&argc, &argv);
    while(*argv) {
        char* endptr;
        int errno_from_arg = (int)strtol(*argv, &endptr, 10);
        if(endptr == *argv) {
            // we don't have an integer, so either it's the '-l' option, or an err name
            if(strcmp("-l", *argv) == 0){
                for(size_t i = 0; i < ERRMAP_SIZE; ++i) {
                    errno = errmap[i].error_no;
                    fprintf(stderr, "%d: ", errno);
                    perror(NULL);
                }
                return 0;
            } else {
                int errmap_pos = lookup_error_byname(*argv);
                if(errmap_pos == -1) {
                    print_error("%s: '%s' is not a number, nor an error name", *argv, program);
                    return 1;
                }
                errno = errmap[errmap_pos].error_no;
            }
        } else {
            errno = errno_from_arg;
        }
        perror(*argv);
        shift_args(&argc, &argv);
    }
    return 0;
}
