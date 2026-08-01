include ../config.mk

# logname is a link to whoami
# md5sum is a link to md5
# [ is a link to test
# how would 'nohup' work on Windows?

PROGS=cat nproc ls uname seq pwd true false yes dirname basename tac sleep wc mktemp tty  base64 base32 mkdir rmdir test mknod whoami readlink dos2unix unix2dos mkfifo cp mv rm sync tee tail head sort shred touch timeout truncate uniq users nice ln install id hostname groups df chroot chmod chown cut date dd fmt fold md5 sha1sum sha224sum sha256sum sha384sum sha512sum pr tr chgrp echo comm du env expand expr join od printf split stty tsort unexpand who nl ed printenv factor nohup numfmt paste pathchk finger realpath stat shuf

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

dos2unix.o: dos2unix.c
	$(CC) $(CFLAGS) -DPROG_PREFIX=\"$(PROG_PREFIX)\" -c $< -o $@

cat: cat.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

nproc: nproc.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

ls: ls.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

uname: uname.o ../lib/prettyprint.o ../lib/utsname_winnt.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

seq: seq.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

pwd: pwd.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

true: true.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

false: false.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

yes: yes.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

dirname: dirname.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

basename: basename.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

tac: tac.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

sleep: sleep.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

wc: wc.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

tr: tr.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

base64: base64.o ../lib/prettyprint.o ../lib/util.o ../lib/base64.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

base32: base32.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

# requires ../libsodium
mktemp: mktemp.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -lsodium -o ../o/bin/$(PROG_PREFIX)$@

mknod: mknod.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/sbin/$(PROG_PREFIX)$@

whoami: whoami.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

tty: tty.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

test: test.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

uniq: uniq.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

mkdir: mkdir.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

rmdir: rmdir.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

head: head.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

tail: tail.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

readlink: readlink.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

dos2unix: dos2unix.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

unix2dos: dos2unix
ifeq ($(WIN32), 1)
		cp ../o/bin/$(PROG_PREFIX)dos2unix.exe ../o/bin/$(PROG_PREFIX)unix2dos.exe
else
		cp ../o/bin/$(PROG_PREFIX)dos2unix ../o/bin/$(PROG_PREFIX)unix2dos
endif

