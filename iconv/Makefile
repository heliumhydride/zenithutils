include ../config.mk

PROGS=iconv

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

iconv: iconv.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

