include ../config.mk

# pkill is a link to kill
# uptime is a link to w
# sysctl: will implement some kind of command line windows control panel?

PROGS=kill pkill w top pstree fuser killall ps sysctl pidof free pgrep vmstat
#ifeq ($(WIN32), 0)
#	PROGS+=sysctl
#endif

all: $(PROGS)

$(PROGS): %: ../o/bin/$(PROG_PREFIX)%
#$(SPROGS): %: ../o/sbin/$(PROG_PREFIX)%

%.o: %.c ../config.h
	@echo "  CC    $(notdir $@)"
	@$(CC) $(CFLAGS) -DPROG_PREFIX=\"$(PROG_PREFIX)\" -c $< -o $@

.SECONDEXPANSION:

../o/bin/$(PROG_PREFIX)%: %.o $$(OBJS)
	@echo "  LD    $(notdir $@)"
	@$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

#../o/sbin/$(PROG_PREFIX)%: %.o $$(OBJS)
#	@echo "  LD    $(notdir $@)"
#	@$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

../o/bin/$(PROG_PREFIX)kill: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)w:    OBJS = ../lib/util.o ../lib/util_m.o

../o/bin/$(PROG_PREFIX)w: LIBS = -lm

# TODO needs testing
ifeq ($(WIN32), 1)
kill.o: kill_win32.c
	@echo "  CC    $(notdir $@)"
	@$(CC) $(CFLAGS) -DPROG_PREFIX=\"$(PROG_PREFIX)\" -c $< -o $@
endif

../o/bin/$(PROG_PREFIX)pkill: ../o/bin/$(PROG_PREFIX)kill
ifeq ($(WIN32), 1)
	@echo "  COPY  $(notdir $(@).exe)"
	@cp $<.exe $@.exe
else
	@echo "  COPY  $(notdir $@)"
	@cp $< $@
endif

.PHONY: all $(PROGS)
