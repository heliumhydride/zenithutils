include ../config.mk

PROGS=xargs find

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

xargs: xargs.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

find: find.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@
