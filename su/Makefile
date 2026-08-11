include ../config.mk

PROGS=su

all: $(PROGS)

%.o: %.c ../config.h
	$(CC) $(CFLAGS) -c $< -o $@

su: su.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

