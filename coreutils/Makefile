include ../config.mk

# logname is a link to whoami
# md5sum is a link to md5
# [ is a link to test
# how would 'nohup' work on Windows?

PROGS=cat nproc ls uname seq pwd true false yes dirname basename tac sleep wc mktemp tty  base64 base32 mkdir rmdir test o/sbin/mknod whoami readlink dos2unix unix2dos mkfifo cp mv rm sync tee tail head sort shred touch timeout truncate uniq users nice ln install id hostname groups df o/sbin/chroot chmod chown cut date dd fmt fold md5 sha1sum sha224sum sha256sum sha384sum sha512sum pr tr chgrp echo comm du env expand expr join od printf split stty tsort unexpand who nl ed printenv factor nohup numfmt paste pathchk finger realpath stat shuf

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

cat: cat.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

nproc: nproc.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

ls: ls.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

uname: uname.o ../lib/prettyprint.o ../lib/utsname_winnt.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

seq: seq.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

pwd: pwd.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

true: true.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

false: false.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

yes: yes.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

dirname: dirname.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

basename: basename.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

tac: tac.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

sleep: sleep.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

wc: wc.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

tr: tr.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

base64: base64.o ../lib/prettyprint.o ../lib/util.o ../lib/base64.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

base32: base32.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

# requires ../libsodium
mktemp: mktemp.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -lsodium -o ../o/bin/$@

mknod: mknod.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

whoami: whoami.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

tty: tty.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

test: test.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

uniq: uniq.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

mkdir: mkdir.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

rmdir: rmdir.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

head: head.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

tail: tail.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

readlink: readlink.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

dos2unix: dos2unix.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

unix2dos: dos2unix
ifeq ($(WIN32), 1)
		cp ../o/bin/dos2unix.exe ../o/bin/unix2dos.exe
else
		cp ../o/bin/dos2unix ../o/bin/unix2dos
endif

readlink: readlink.o lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

readlink: readlink.o lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

readlink: readlink.o lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

readlink: readlink.o lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

