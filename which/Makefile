include ../config.mk

PROGS=which

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

which: which.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

