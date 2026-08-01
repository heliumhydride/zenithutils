include ../config.mk

PROGS=sed

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

sed: sed.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

