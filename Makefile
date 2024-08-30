include config.mk

all: customtools coreutils which sharutils util-linux findutils sed procutils diffutils grep patch su gzip iconv

# yes read, like the shellscript read (with -r, and all that good stuff)
customtools: o/usr/bin/zenithutils_version o/usr/bin/ascii o/usr/bin/rng o/usr/bin/read o/usr/bin/strings o/usr/bin/exedump o/usr/bin/usleep o/usr/bin/time o/usr/bin/lsmod

# logname is a link to whoami
# md5sum is a link to md5
coreutils: o/bin/cat o/usr/bin/nproc o/bin/ls o/usr/bin/uname o/usr/bin/seq o/bin/pwd o/usr/bin/true o/usr/bin/false o/usr/bin/yes o/usr/bin/dirname o/usr/bin/basename o/usr/bin/tac o/usr/bin/sleep o/usr/bin/wc o/usr/bin/mktemp o/sbin/mknod o/usr/bin/mkfifo o/bin/cp o/bin/mv o/bin/rm o/usr/bin/readlink o/bin/rmdir o/bin/mkdir o/bin/sync o/bin/test o/usr/bin/tee o/usr/bin/tail o/usr/bin/head o/usr/bin/sort o/usr/bin/shred o/bin/touch o/usr/bin/timeout o/usr/bin/truncate o/usr/bin/uniq o/usr/bin/users o/usr/bin/whoami o/usr/bin/nice o/bin/ln o/usr/bin/install o/usr/bin/id o/usr/bin/hostname o/usr/bin/groups o/usr/bin/df o/usr/sbin/chroot o/usr/bin/[ o/bin/chmod o/bin/chown o/bin/cut o/bin/date o/bin/dd o/usr/bin/fmt o/usr/bin/fold o/usr/bin/md5 o/usr/bin/sha1sum o/usr/bin/sha224sum o/usr/bin/sha256sum o/usr/bin/sha384sum o/usr/bin/sha512sum o/usr/bin/pr o/usr/bin/tr o/usr/bin/base64 o/usr/bin/base32 o/bin/chgrp o/bin/echo o/usr/bin/comm o/usr/bin/du o/usr/bin/env o/usr/bin/expand o/usr/bin/expr o/usr/bin/join o/usr/bin/od o/usr/bin/printf o/usr/bin/split o/usr/bin/stty o/usr/bin/tsort o/usr/bin/tty o/usr/bin/unexpand o/usr/bin/who o/usr/bin/nl

# do we really need 'rename' and 'hardlink' ? (see 'mv' and 'ln')
# agetty not implemented, see nyagetty from chimera linux
# hwclock not being implemented for now
# losetup, login, mkswap, pivot_root, ionice, write, show a "does not apply to windows" and return 1
# fsck on windows: do we just 'execvp("chkdsk.exe", ...);' ?
util-linux: o/usr/bin/rev o/usr/sbin/nologin o/usr/bin/uuidgen o/usr/bin/lscpu o/bin/kill o/usr/bin/blkid o/usr/bin/cal o/usr/bin/cfdisk o/usr/bin/chsh o/usr/bin/col o/usr/bin/dmesg o/usr/bin/eject o/usr/bin/fallocate o/sbin/fdisk o/usr/bin/findfs o/sbin/fsck o/usr/bin/getopt o/usr/bin/hexdump o/usr/bin/ionice o/usr/bin/last o/usr/bin/login o/usr/sbin/losetup o/usr/bin/lsblk o/usr/bin/lslogins o/usr/bin/mcookie o/sbin/mkfs o/sbin/mkswap o/bin/more o/sbin/mount o/usr/bin/mountpoint o/usr/sbin/pivot_root o/usr/bin/renice o/usr/bin/write o/usr/bin/whereis

findutils: o/usr/bin/xargs o/usr/bin/find 

diffutils: o/usr/bin/diff o/usr/bin/cmp o/usr/bin/sdiff

su: o/bin/su

which: o/usr/bin/which

# egrep and fgrep are links to grep
grep: o/usr/bin/grep

sed: o/usr/bin/sed

patch: o/usr/bin/patch

# gunzip and zcat are links to gzip
gzip: o/usr/bin/gzip

# sysctl will either show a "does not apply to windows" or will implement some kind of command line windows control panel
# what do we do for sysctl on *BSD ???
procutils: o/usr/bin/top o/usr/bin/pstree o/usr/bin/fuser o/usr/bin/killall o/usr/bin/ps o/usr/bin/w o/usr/bin/pkill o/sbin/sysctl o/usr/bin/uptime o/usr/bin/pidof o/usr/bin/free o/usr/bin/pgrep

sharutils: o/usr/bin/shar o/usr/bin/uuencode o/usr/bin/uudecode

iconv: o/usr/bin/iconv

o/usr/bin/zenithutils_version: init_outdir customtools/zenithutils_version.c
	$(CC) $(CFLAGS) -o o/usr/bin/zenithutils_version customtools/zenithutils_version.c

lib/prettyprint.o: lib/prettyprint.c
	$(CC) $(CFLAGS) -c -o lib/prettyprint.o lib/prettyprint.c

coreutils/cat.o: coreutils/cat.c
	$(CC) $(CFLAGS) -c -o coreutils/cat.o coreutils/cat.c

o/bin/cat: init_outdir lib/prettyprint.o lib/util.o coreutils/cat.o
	$(LD) $(LDFLAGS) -o o/bin/cat lib/prettyprint.o lib/util.o coreutils/cat.o

o/usr/bin/nproc: init_outdir coreutils/nproc.c
	$(CC) $(CFLAGS) -o o/usr/bin/nproc coreutils/nproc.c

coreutils/ls.o: coreutils/ls.c
	$(CC) $(CFLAGS) -c -o coreutils/ls.o coreutils/ls.c

o/bin/ls: init_outdir lib/prettyprint.o lib/util.o coreutils/ls.o
	$(LD) $(LDFLAGS) -o o/bin/ls lib/prettyprint.o lib/util.o coreutils/ls.o

lib/utsname_winnt.o: lib/utsname_winnt.c
	$(CC) $(CFLAGS) -c -o lib/utsname_winnt.o lib/utsname_winnt.c

coreutils/uname.o: coreutils/uname.c
	$(CC) $(CFLAGS) -c -o coreutils/uname.o coreutils/uname.c

o/usr/bin/uname: init_outdir lib/prettyprint.o lib/utsname_winnt.o coreutils/uname.o
	$(LD) $(LDFLAGS) -o o/usr/bin/uname lib/prettyprint.o lib/utsname_winnt.o coreutils/uname.o 

lib/util.o: lib/util.c
	$(CC) $(CFLAGS) -c -o lib/util.o lib/util.c

which/which.o: which/which.c
	$(CC) $(CFLAGS) -c -o which/which.o which/which.c

o/usr/bin/which: init_outdir lib/prettyprint.o lib/util.o which/which.o
	$(LD) $(LDFLAGS) -o o/usr/bin/which lib/prettyprint.o lib/util.o which/which.o 

coreutils/seq.o: coreutils/seq.c
	$(CC) $(CFLAGS) -c -o coreutils/seq.o coreutils/seq.c

o/usr/bin/seq: init_outdir lib/prettyprint.o lib/util.o coreutils/seq.o
	$(LD) $(LDFLAGS) -o o/usr/bin/seq lib/prettyprint.o lib/util.o coreutils/seq.o 

o/bin/pwd: init_outdir lib/prettyprint.o coreutils/pwd.o
	$(LD) $(LDFLAGS) -o o/bin/pwd lib/prettyprint.o coreutils/pwd.o 

o/usr/bin/true: init_outdir coreutils/true.c
	$(CC) $(CFLAGS) -o o/usr/bin/true coreutils/true.c

o/usr/bin/false: init_outdir coreutils/false.c
	$(CC) $(CFLAGS) -o o/usr/bin/false coreutils/false.c

o/usr/bin/yes: init_outdir coreutils/yes.c
	$(CC) $(CFLAGS) -o o/usr/bin/yes coreutils/yes.c

o/usr/bin/dirname: init_outdir coreutils/dirname.c
	$(CC) $(CFLAGS) -o o/usr/bin/dirname coreutils/dirname.c

o/usr/bin/basename: init_outdir coreutils/basename.c
	$(CC) $(CFLAGS) -o o/usr/bin/basename coreutils/basename.c

coreutils/tac.o: coreutils/tac.c
	$(CC) $(CFLAGS) -c -o coreutils/tac.o coreutils/tac.c

o/usr/bin/tac: init_outdir lib/prettyprint.o lib/util.o coreutils/tac.o
	$(LD) $(LDFLAGS) -o o/usr/bin/tac lib/prettyprint.o lib/util.o coreutils/tac.o

o/usr/bin/sleep: init_outdir coreutils/sleep.c
	$(CC) $(CFLAGS) -o o/usr/bin/sleep coreutils/sleep.c

coreutils/wc.o: coreutils/wc.c
	$(CC) $(CFLAGS) -c -o coreutils/wc.o coreutils/wc.c

o/usr/bin/wc: init_outdir lib/prettyprint.o lib/util.o coreutils/wc.o
	$(LD) $(LDFLAGS) -o o/usr/bin/wc lib/prettyprint.o lib/util.o coreutils/wc.o

coreutils/tr.o: coreutils/tr.c
	$(CC) $(CFLAGS) -c -o coreutils/tr.o coreutils/tr.c

o/usr/bin/tr: init_outdir lib/prettyprint.o lib/util.o coreutils/tr.o
	$(LD) $(LDFLAGS) -o o/usr/bin/tr lib/prettyprint.o lib/util.o coreutils/tr.o

coreutils/base64.o: coreutils/base64.c config.h
	$(CC) $(CFLAGS) -c -o coreutils/base64.o coreutils/base64.c

o/usr/bin/base64: init_outdir lib/prettyprint.o lib/util.o coreutils/base64.o
	$(LD) $(LDFLAGS) -o o/usr/bin/base64 lib/prettyprint.o lib/util.o coreutils/base64.o 

coreutils/base32.o: coreutils/base32.c config.h
	$(CC) $(CFLAGS) -c -o coreutils/base32.o coreutils/base32.c

o/usr/bin/base32: init_outdir lib/prettyprint.o coreutils/base32.o
	$(LD) $(LDFLAGS) -o o/usr/bin/base32 lib/prettyprint.o coreutils/base32.o 

o/usr/bin/shar: init_outdir sharutils/shar.sh
	cp sharutils/shar.sh o/usr/bin/shar

sharutils/uuencode.o: sharutils/uuencode.c
	$(CC) $(CFLAGS) -c -o sharutils/uuencode.o sharutils/uuencode.c

o/usr/bin/uuencode: init_outdir lib/prettyprint.o lib/util.o sharutils/uuencode.o
	$(LD) $(LDFLAGS) -o o/usr/bin/uuencode lib/prettyprint.o lib/util.o sharutils/uuencode.o 

sharutils/uudecode.o: sharutils/uudecode.c
	$(CC) $(CFLAGS) -c -o sharutils/uudecode.o sharutils/uudecode.c

o/usr/bin/uudecode: init_outdir lib/prettyprint.o lib/util.o sharutils/uudecode.o
	$(LD) $(LDFLAGS) -o o/usr/bin/uudecode lib/prettyprint.o lib/util.o sharutils/uudecode.o 

coreutils/mktemp.o: coreutils/mktemp.c
	$(CC) $(CFLAGS) -c -o coreutils/mktemp.o coreutils/mktemp.c

# requires libsodium
o/usr/bin/mktemp: init_outdir lib/prettyprint.o coreutils/mktemp.o
	$(LD) $(LDFLAGS) -o o/usr/bin/mktemp lib/prettyprint.o -lsodium coreutils/mktemp.o

coreutils/mknod.o: coreutils/mknod.c
	$(CC) $(CFLAGS) -c -o coreutils/mknod.o coreutils/mknod.c

o/sbin/mknod: init_outdir lib/prettyprint.o coreutils/mknod.o
	$(LD) $(LDFLAGS) -o o/sbin/mknod lib/prettyprint.o coreutils/mknod.o 

coreutils/mkfifo.o: coreutils/mkfifo.c
	$(CC) $(CFLAGS) -c -o coreutils/mkfifo.o coreutils/mkfifo.c

o/usr/bin/mkfifo: init_outdir lib/prettyprint.o coreutils/mkfifo.o
	$(LD) $(LDFLAGS) -o o/usr/bin/mkfifo lib/prettyprint.o coreutils/mkfifo.o

customtools/read.o: customtools/read.c
	$(CC) $(CFLAGS) -c -o customtools/read.o customtools/read.c

o/usr/bin/read: init_outdir lib/prettyprint.o customtools/read.o
	$(LD) $(LDFLAGS) -o o/usr/bin/read lib/prettyprint.o customtools/read.o

customtools/strings.o: customtools/strings.c
	$(CC) $(CFLAGS) -c -o customtools/strings.o customtools/strings.c

o/usr/bin/strings: init_outdir lib/prettyprint.o customtools/strings.o
	$(LD) $(LDFLAGS) -o o/usr/bin/strings lib/prettyprint.o customtools/strings.o

o/usr/bin/ascii: init_outdir customtools/ascii.c
	$(CC) $(CFLAGS) -o o/usr/bin/ascii customtools/ascii.c

util-linux/rev.o: util-linux/rev.c
	$(CC) $(CFLAGS) -c -o util-linux/rev.o util-linux/rev.c

o/usr/bin/rev: init_outdir lib/prettyprint.o lib/util.o util-linux/rev.o
	$(LD) $(LDFLAGS) -o o/usr/bin/rev lib/prettyprint.o lib/util.o util-linux/rev.o

o/usr/sbin/nologin: init_outdir util-linux/nologin.c
	$(CC) $(CFLAGS) -o o/usr/sbin/nologin util-linux/nologin.c

util-linux/uuidgen.o: util-linux/uuidgen.c
	$(CC) $(CFLAGS) -c -o util-linux/uuidgen.o util-linux/uuidgen.c

# requires libsodium
o/usr/bin/uuidgen: init_outdir lib/prettyprint.o lib/util.o util-linux/uuidgen.o
	$(LD) $(LDFLAGS) -o o/usr/bin/uuidgen lib/prettyprint.o lib/util.o -lsodium util-linux/uuidgen.o

findutils/xargs.o: findutils/xargs.c
	$(CC) $(CFLAGS) -c -o findutils/xargs.o findutils/xargs.c

o/usr/bin/xargs: init_outdir lib/prettyprint.o findutils/xargs.o
	$(LD) $(LDFLAGS) -o o/usr/bin/xargs lib/prettyprint.o findutils/xargs.o

customtools/rng.o: customtools/rng.c
	$(CC) $(CFLAGS) -c -o customtools/rng.o customtools/rng.c

# requires libsodium
o/usr/bin/rng: init_outdir lib/prettyprint.o lib/util.o customtools/rng.o
	$(LD) $(LDFLAGS) -o o/usr/bin/rng lib/prettyprint.o lib/util.o -lsodium customtools/rng.o

customtools/exedump.o: customtools/exedump.c config.h
	$(CC) $(CFLAGS) -c -o customtools/exedump.o customtools/exedump.c

o/usr/bin/exedump: init_outdir lib/prettyprint.o customtools/exedump.o
	$(LD) $(LDFLAGS) -o o/usr/bin/exedump lib/prettyprint.o customtools/exedump.o

customtools/usleep.o: customtools/usleep.c
	$(CC) $(CFLAGS) -c -o customtools/usleep.o customtools/usleep.c

o/usr/bin/usleep: init_outdir lib/prettyprint.o lib/util.o customtools/usleep.o
	$(LD) $(LDFLAGS) -o o/usr/bin/usleep lib/prettyprint.o lib/util.o customtools/usleep.o

clean:
	rm -rf o/* customtools/*.o coreutils/*.o diffutils/*.o findutils/*.o grep/*.o gzip/*.o lib/*.o patch/*.o procutils/*.o sed/*.o sh/*.o su/*.o tar/*.o util-linux/*.o which/*.o sharutils/*.o cpio/*.o

init_outdir: o/bin o/sbin o/usr/bin o/usr/sbin

o/bin:
	mkdir -p $@

o/sbin:
	mkdir -p $@

o/usr/bin:
	mkdir -p $@

o/usr/sbin:
	mkdir -p $@

.PHONY: clean all init_outdir install
