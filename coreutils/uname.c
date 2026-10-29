#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "../include/prettyprint.h"

#ifdef _WIN32
  // #include <sysinfoapi.h>
  #include "../include/utsname_winnt.h"
#else // On Unix
  #include <sys/utsname.h>
#endif

void print_usage(const char* program)
{
  fprintf(stderr, "usage: %s [-asnrvmpio]\n", program);
}

void print_sysname(struct utsname u)
{
    printf("%s ", u.sysname);
}

void print_nodename(struct utsname u)
{
    printf("%s ", u.nodename);
}

void print_release(struct utsname u)
{
    printf("%s ", u.release);
}

void print_version(struct utsname u)
{
    printf("%s ", u.version);
}

void print_machine(struct utsname u)
{
    printf("%s ", u.machine);
}

void print_os(struct utsname u)
{
    #ifdef _WIN32
    printf("Windows ");
    #else // On Unix
    print_sysname(u);
    #endif
}

int main(int argc, char* argv[])
{
    // opts: -asnrvmpio
    int sflag = 0;
    int nflag = 0;
    int rflag = 0;
    int vflag = 0;
    int mflag = 0;
    int pflag = 0; // -p == -m
    int iflag = 0; // -i == -m
    int oflag = 0;

    int opt;
    while((opt = getopt(argc, argv, ":asnrvmpio")) != -1) {
        switch(opt) {
            case 'a':
                sflag = nflag = rflag = vflag = mflag = oflag = 1;
              //sflag = nflag = rflag = vflag = mflag = pflag = iflag = oflag = 1; // in case we want -p and -i to be set with -a
                break;
            case 's':
                sflag = 1;
                break;
            case 'n':
                nflag = 1;
                break;
            case 'r':
                rflag = 1;
                break;
            case 'v':
                vflag = 1;
                break;
            case 'm':
                mflag = 1;
                break;
            case 'p':
                pflag = 1;
                break;
            case 'i':
                iflag = 1;
                break;
            case 'o':
                oflag = 1;
                break;
            case '?':
                print_error("%s: invalid option -- '%c'", argv[0], optopt);
                print_usage(argv[0]);
                return 1;
                break;
        }
    }
    
    // no options are set, default to -s
    if(sflag == 0 && nflag == 0 && rflag == 0 && vflag == 0 && mflag == 0 && pflag == 0 && iflag == 0 && oflag == 0)  sflag = 1;

    struct utsname u;
    uname(&u);

    if(sflag) print_sysname(u);
    if(nflag) print_nodename(u);
    if(rflag) print_release(u);
    if(vflag) print_version(u);
    if(mflag) print_machine(u);
    if(pflag) print_machine(u);
    if(iflag) print_machine(u);
    if(oflag) print_os(u);

    putchar('\n');
    return 0;
}
