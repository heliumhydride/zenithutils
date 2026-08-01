include ../config.mk

PROGS=grep egrep fgrep

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

grep: grep.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

egrep: egrep.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

fgrep: fgrep.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

