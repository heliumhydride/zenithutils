#ifndef SIGMAP_H
#define SIGMAP_H

typedef struct {
  const char *opt;
  int sig;
} sigmap_t;

#ifdef __linux__
const sigmap_t sigmap[] = {
  {"-SIGHUP",   SIGHUP},   {"-HUP",   SIGHUP},   {"-1",  SIGHUP},
  {"-SIGINT",   SIGINT},   {"-INT",   SIGINT},   {"-2",  SIGINT},
  {"-SIGQUIT",  SIGQUIT},  {"-QUIT",  SIGQUIT},  {"-3",  SIGQUIT},
  {"-SIGILL",   SIGILL},   {"-ILL",   SIGILL},   {"-4",  SIGILL},
  {"-SIGTRAP",  SIGTRAP},  {"-TRAP",  SIGTRAP},  {"-5",  SIGTRAP},
  {"-SIGABRT",  SIGABRT},  {"-ABRT",  SIGABRT},  {"-6",  SIGABRT},
  {"-SIGBUS",   SIGBUS},   {"-BUS",   SIGBUS},   {"-7",  SIGBUS},
  {"-SIGFPE",   SIGFPE},   {"-FPE",   SIGFPE},   {"-8",  SIGFPE},
  {"-SIGKILL",  SIGKILL},  {"-KILL",  SIGKILL},  {"-9",  SIGKILL},
  {"-SIGUSR1",  SIGUSR1},  {"-USR1",  SIGUSR1},  {"-10", SIGUSR1},
  {"-SIGSEGV",  SIGSEGV},  {"-SEGV",  SIGSEGV},  {"-11", SIGSEGV},
  {"-SIGUSR2",  SIGUSR2},  {"-USR2",  SIGUSR2},  {"-12", SIGUSR2},
  {"-SIGPIPE",  SIGPIPE},  {"-PIPE",  SIGPIPE},  {"-13", SIGPIPE},
  {"-SIGALRM",  SIGALRM},  {"-ALRM",  SIGALRM},  {"-14", SIGALRM},
  {"-SIGTERM",  SIGTERM},  {"-TERM",  SIGTERM},  {"-15", SIGTERM},
  {"-SIGCHLD",  SIGCHLD},  {"-CHLD",  SIGCHLD},  {"-17", SIGCHLD},
  {"-SIGCONT",  SIGCONT},  {"-CONT",  SIGCONT},  {"-18", SIGCONT},
  {"-SIGSTOP",  SIGSTOP},  {"-STOP",  SIGSTOP},  {"-19", SIGSTOP},
  {"-SIGTSTP",  SIGTSTP},  {"-TSTP",  SIGTSTP},  {"-20", SIGTSTP},
  {"-SIGTTIN",  SIGTTIN},  {"-TTIN",  SIGTTIN},  {"-21", SIGTTIN},
  {"-SIGTTOU",  SIGTTOU},  {"-TTOU",  SIGTTOU},  {"-22", SIGTTOU},
  {"-SIGURG",   SIGURG},   {"-URG",   SIGURG},   {"-23", SIGURG},
  {"-SIGXCPU",  SIGXCPU},  {"-XCPU",  SIGXCPU},  {"-24", SIGXCPU},
  {"-SIGXFSZ",  SIGXFSZ},  {"-XFSZ",  SIGXFSZ},  {"-25", SIGXFSZ},
  {"-SIGPROF",  SIGPROF},  {"-PROF",  SIGPROF},  {"-27", SIGPROF},
  {"-SIGWINCH", SIGWINCH}, {"-WINCH", SIGWINCH}, {"-28", SIGWINCH},
  {"-SIGIO",    SIGIO},    {"-IO",    SIGIO},    {"-29", SIGIO},
  {"-SIGSYS",   SIGSYS},   {"-SYS",   SIGSYS},   {"-31", SIGSYS}
};
#else
#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)
#include <sys/signal.h>
const sigmap_t sigmap[] = {
  {"-SIGHUP",   SIGHUP},   {"-HUP",   SIGHUP},   {"-1",  SIGHUP},
  {"-SIGINT",   SIGINT},   {"-INT",   SIGINT},   {"-2",  SIGINT},
  {"-SIGQUIT",  SIGQUIT},  {"-QUIT",  SIGQUIT},  {"-3",  SIGQUIT},
  {"-SIGILL",   SIGILL},   {"-ILL",   SIGILL},   {"-4",  SIGILL},
  {"-SIGTRAP",  SIGTRAP},  {"-TRAP",  SIGTRAP},  {"-5",  SIGTRAP},
  {"-SIGABRT",  SIGABRT},  {"-ABRT",  SIGABRT},  {"-6",  SIGABRT},
  {"-SIGEMT",   SIGEMT},   {"-EMT",   SIGEMT},   {"-7",  SIGEMT},
  {"-SIGFPE",   SIGFPE},   {"-FPE",   SIGFPE},   {"-8",  SIGFPE},
  {"-SIGKILL",  SIGKILL},  {"-KILL",  SIGKILL},  {"-9",  SIGKILL},
  {"-SIGBUS",   SIGBUS},   {"-BUS",   SIGBUS},   {"-10", SIGBUS},
  {"-SIGSEGV",  SIGSEGV},  {"-SEGV",  SIGSEGV},  {"-11", SIGSEGV},
  {"-SIGSYS",   SIGSYS},   {"-SYS",   SIGSYS},   {"-12", SIGSYS},
  {"-SIGPIPE",  SIGPIPE},  {"-PIPE",  SIGPIPE},  {"-13", SIGPIPE},
  {"-SIGALRM",  SIGALRM},  {"-ALRM",  SIGALRM},  {"-14", SIGALRM},
  {"-SIGTERM",  SIGTERM},  {"-TERM",  SIGTERM},  {"-15", SIGTERM},
  {"-SIGURG",   SIGURG},   {"-URG",   SIGURG},   {"-16", SIGURG},
  {"-SIGSTOP",  SIGSTOP},  {"-STOP",  SIGSTOP},  {"-17", SIGSTOP},
  {"-SIGTSTP",  SIGTSTP},  {"-TSTP",  SIGTSTP},  {"-18", SIGTSTP},
  {"-SIGCONT",  SIGCONT},  {"-CONT",  SIGCONT},  {"-19", SIGCONT},
  {"-SIGCHLD",  SIGCHLD},  {"-CHLD",  SIGCHLD},  {"-20", SIGCHLD},
  {"-SIGTTIN",  SIGTTIN},  {"-TTIN",  SIGTTIN},  {"-21", SIGTTIN},
  {"-SIGTTOU",  SIGTTOU},  {"-TTOU",  SIGTTOU},  {"-22", SIGTTOU},
  {"-SIGIO",    SIGIO},    {"-IO",    SIGIO},    {"-23", SIGIO},
  {"-SIGXCPU",  SIGXCPU},  {"-XCPU",  SIGXCPU},  {"-24", SIGXCPU},
  {"-SIGXFSZ",  SIGXFSZ},  {"-XFSZ",  SIGXFSZ},  {"-25", SIGXFSZ},
  {"-SIGVTALRM", SIGVTALRM},{"-VTALRM", SIGVTALRM},{"-26", SIGVTALRM},
  {"-SIGPROF",  SIGPROF},  {"-PROF",  SIGPROF},  {"-27", SIGPROF},
  {"-SIGWINCH", SIGWINCH}, {"-WINCH", SIGWINCH}, {"-28", SIGWINCH},
  {"-SIGINFO",  SIGINFO},  {"-INFO",  SIGINFO},  {"-29", SIGINFO},
  {"-SIGUSR1",  SIGUSR1},  {"-USR1",  SIGUSR1},  {"-30", SIGUSR1},
  {"-SIGUSR2",  SIGUSR2},  {"-USR2",  SIGUSR2},  {"-31", SIGUSR2},
};
#else
const sigmap_t sigmap[] = {{NULL,0}};
#endif // __FreeBSD__ // __OpenBSD__
#endif // __linux__
#endif // SIGMAP_H
