include ../config.mk

# sysctl will either show a "does not apply to windows" or will implement some kind of command line windows control panel
# pkill is a link to kill
# uptime is a link to w

PROGS=kill pkill w top pstree fuser killall ps sysctl pidof free pgrep vmstat

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kill.o: kill.c
ifeq ($(WIN32), 1)
	$(CC) $(CFLAGS) -c kill_win32.c -o kill.o
else
	$(CC) $(CFLAGS) -c kill.c -o kill.o
endif

kill: kill.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

pkill: kill
ifeq ($(WIN32), 1)
	cp ../o/bin/kill.exe ../o/bin/pkill.exe
else
	cp ../o/bin/kill ../o/bin/pkill
endif

w: w.o ../lib/prettyprint.o ../lib/util.o ../lib/util_m.o
	$(LD) $(LDFLAGS) $^ -lm -o ../o/bin/$@ 
