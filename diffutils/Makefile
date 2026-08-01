include ../config.mk

PROGS=diff cmp sdiff

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

diff: diff.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

cmp: cmp.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

sdiff: sdiff.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

