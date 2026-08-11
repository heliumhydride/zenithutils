include ../config.mk

PROGS=iconv

all: $(PROGS)

%.o: %.c ../config.h
	$(CC) $(CFLAGS) -c $< -o $@

iconv: iconv.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

