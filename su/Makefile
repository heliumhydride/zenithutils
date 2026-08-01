include ../config.mk

PROGS=su

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

su: su.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

