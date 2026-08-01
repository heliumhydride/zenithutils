include ../config.mk

PROGS=gzip gunzip zcat

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

gzip: gzip.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

gunzip: gunzip.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

zcat: zcat.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

