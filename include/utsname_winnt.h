#ifndef UTSNAME_WINNT_H
#define UTSNAME_WINNT_H

struct utsname {
        char sysname[65];
        char nodename[65];
        char release[65];
        char version[65];
        char machine[65];
};

int uname(struct utsname* uts);

#endif
