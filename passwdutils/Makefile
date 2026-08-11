include ../config.mk

# TODO note to self: chage, useradd, userdel, usermod, groupadd, groupdel, groupmod, sg are in /sbin
PROGS=passwd chage useradd userdel usermod groupadd groupdel groupmod sg

all: $(PROGS)

%.o: %.c ../config.h
	$(CC) $(CFLAGS) -c $< -o $@

passwd: passwd.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

