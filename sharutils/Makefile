include ../config.mk

PROGS=shar uuencode uudecode

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

shar: shar.sh
	cp shar.sh ../o/bin/$(PROG_PREFIX)shar

uuencode: uuencode.o ../lib/prettyprint.o ../lib/base64.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

udecode: uudecode.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

