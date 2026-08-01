include ../config.mk

PROGS=diff cmp sdiff

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

diff: diff.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

cmp: cmp.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

sdiff: sdiff.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

