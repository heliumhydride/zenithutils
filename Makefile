include config.mk

all: coreutils customtools diffutils findutils grep gzip iconv patch procutils sed sharutils su util-linux which passwdutils

# yes read, like the shellscript read (with -r, and all that good stuff)
customtools: o/usr/bin/zenithutils_version o/usr/bin/ascii o/usr/bin/rng o/usr/bin/read o/usr/bin/strings o/usr/bin/exedump o/usr/bin/usleep o/usr/bin/clear o/usr/bin/time

# logname is a link to whoami
# md5sum is a link to md5
# [ is a link to test
coreutils: o/bin/cat o/usr/bin/nproc o/bin/ls o/usr/bin/uname o/usr/bin/seq o/bin/pwd o/usr/bin/true o/usr/bin/false o/usr/bin/yes o/usr/bin/dirname o/usr/bin/basename o/usr/bin/tac o/usr/bin/sleep o/usr/bin/wc o/usr/bin/mktemp o/usr/bin/tty  o/usr/bin/base64 o/usr/bin/base32 o/bin/mkdir o/bin/rmdir o/bin/test o/sbin/mknod o/usr/bin/whoami o/usr/bin/mkfifo o/bin/cp o/bin/mv o/bin/rm o/usr/bin/readlink o/bin/sync o/usr/bin/tee o/usr/bin/tail o/usr/bin/head o/usr/bin/sort o/usr/bin/shred o/bin/touch o/usr/bin/timeout o/usr/bin/truncate o/usr/bin/uniq o/usr/bin/users o/usr/bin/nice o/bin/ln o/usr/bin/install o/usr/bin/id o/usr/bin/hostname o/usr/bin/groups o/usr/bin/df o/usr/sbin/chroot o/bin/chmod o/bin/chown o/bin/cut o/bin/date o/bin/dd o/usr/bin/fmt o/usr/bin/fold o/usr/bin/md5 o/usr/bin/sha1sum o/usr/bin/sha224sum o/usr/bin/sha256sum o/usr/bin/sha384sum o/usr/bin/sha512sum o/usr/bin/pr o/usr/bin/tr o/bin/chgrp o/bin/echo o/usr/bin/comm o/usr/bin/du o/usr/bin/env o/usr/bin/expand o/usr/bin/expr o/usr/bin/join o/usr/bin/od o/usr/bin/printf o/usr/bin/split o/usr/bin/stty o/usr/bin/tsorto/usr/bin/unexpand o/usr/bin/who o/usr/bin/nl o/usr/bin/dos2unix o/usr/bin/unix2dos o/usr/bin/ed o/usr/bin/printenv

# do we really need 'rename' and 'hardlink' ? (see 'mv' and 'ln')
# agetty not implemented, see nyagetty from chimera linux
# hwclock not being implemented for now
# losetup, pivot_root, ionice, write, show a "does not apply to windows" and return 1
# for mkswap/swapon/swapoff on windows: do we have functions in the win32 api to change pagefile settings ?
# for login on windows: use as a frontend to LogonUI/runas.exe maybe ? kind of a strech but I don't see what else login.exe would do...
# fsck on windows: do we just 'execvp("chkdsk.exe", ...);' ?
util-linux: o/usr/bin/rev o/usr/sbin/nologin o/usr/bin/uuidgen o/bin/kill o/usr/bin/lscpu o/usr/bin/column o/usr/bin/blkid o/usr/bin/cal o/usr/bin/cfdisk o/usr/bin/chsh o/usr/bin/col o/usr/bin/dmesg o/usr/bin/eject o/usr/bin/fallocate o/sbin/fdisk o/usr/bin/findfs o/sbin/fsck o/usr/bin/getopt o/usr/bin/hexdump o/usr/bin/ionice o/usr/bin/last o/usr/bin/login o/usr/sbin/losetup o/usr/bin/lsblk o/usr/bin/lslogins o/usr/bin/mcookie o/sbin/mkfs o/sbin/mkswap o/bin/more o/sbin/mount o/usr/bin/mountpoint o/usr/sbin/pivot_root o/usr/bin/renice o/usr/bin/write o/usr/bin/whereis o/usr/bin/swapon o/usr/bin/swapoff

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
# uptime is a link to w
procutils: o/usr/bin/w o/usr/bin/top o/usr/bin/pstree o/usr/bin/fuser o/usr/bin/killall o/usr/bin/ps o/usr/bin/pkill o/sbin/sysctl o/usr/bin/pidof o/usr/bin/free o/usr/bin/pgrep

sharutils: o/usr/bin/shar o/usr/bin/uuencode o/usr/bin/uudecode

iconv: o/usr/bin/iconv

passwdutils: o/usr/bin/passwd o/usr/sbin/chage o/usr/sbin/useradd o/usr/sbin/userdel o/usr/sbin/usermod o/usr/sbin/groupadd o/usr/sbin/groupdel o/usr/sbin/groupmod

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

lib/util_m.o: lib/util_m.c
	$(CC) $(CFLAGS) -c -o lib/util_m.o lib/util_m.c

which/which.o: which/which.c
	$(CC) $(CFLAGS) -c -o which/which.o which/which.c

o/usr/bin/which: init_outdir lib/prettyprint.o lib/util.o which/which.o
	$(LD) $(LDFLAGS) -o o/usr/bin/which lib/prettyprint.o lib/util.o which/which.o 

coreutils/seq.o: coreutils/seq.c
	$(CC) $(CFLAGS) -c -o coreutils/seq.o coreutils/seq.c

o/usr/bin/seq: init_outdir lib/prettyprint.o lib/util.o coreutils/seq.o
	$(LD) $(LDFLAGS) -o o/usr/bin/seq lib/prettyprint.o lib/util.o coreutils/seq.o 

o/bin/pwd: init_outdir lib/prettyprint.o lib/util.o coreutils/pwd.o
	$(LD) $(LDFLAGS) -o o/bin/pwd lib/prettyprint.o lib/util.o coreutils/pwd.o 

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

o/usr/bin/base64: init_outdir lib/prettyprint.o lib/util.o lib/base64.o coreutils/base64.o
	$(LD) $(LDFLAGS) -o o/usr/bin/base64 lib/prettyprint.o lib/util.o lib/base64.o coreutils/base64.o 

coreutils/base32.o: coreutils/base32.c config.h
	$(CC) $(CFLAGS) -c -o coreutils/base32.o coreutils/base32.c

o/usr/bin/base32: init_outdir lib/prettyprint.o lib/util.o coreutils/base32.o
	$(LD) $(LDFLAGS) -o o/usr/bin/base32 lib/prettyprint.o lib/util.o coreutils/base32.o 

o/usr/bin/shar: init_outdir sharutils/shar.sh
	cp sharutils/shar.sh o/usr/bin/shar

sharutils/uuencode.o: sharutils/uuencode.c lib/base64.o
	$(CC) $(CFLAGS) -c -o sharutils/uuencode.o lib/base64.o sharutils/uuencode.c

o/usr/bin/uuencode: init_outdir lib/prettyprint.o lib/base64.o sharutils/uuencode.o
	$(LD) $(LDFLAGS) -o o/usr/bin/uuencode lib/prettyprint.o lib/base64.o sharutils/uuencode.o 

sharutils/uudecode.o: sharutils/uudecode.c
	$(CC) $(CFLAGS) -c -o sharutils/uudecode.o sharutils/uudecode.c

o/usr/bin/uudecode: init_outdir lib/prettyprint.o lib/util.o sharutils/uudecode.o
	$(LD) $(LDFLAGS) -o o/usr/bin/uudecode lib/prettyprint.o lib/util.o sharutils/uudecode.o 

coreutils/mktemp.o: coreutils/mktemp.c
	$(CC) $(CFLAGS) -c -o coreutils/mktemp.o coreutils/mktemp.c

# requires libsodium
o/usr/bin/mktemp: init_outdir lib/prettyprint.o lib/util.o coreutils/mktemp.o
	$(LD) $(LDFLAGS) -o o/usr/bin/mktemp lib/prettyprint.o lib/util.o coreutils/mktemp.o -lsodium

coreutils/mknod.o: coreutils/mknod.c
	$(CC) $(CFLAGS) -c -o coreutils/mknod.o coreutils/mknod.c

o/sbin/mknod: init_outdir lib/prettyprint.o lib/util.o coreutils/mknod.o
	$(LD) $(LDFLAGS) -o o/sbin/mknod lib/prettyprint.o lib/util.o coreutils/mknod.o 

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

o/usr/bin/strings: init_outdir lib/prettyprint.o lib/util.o customtools/strings.o
	$(LD) $(LDFLAGS) -o o/usr/bin/strings lib/prettyprint.o lib/util.o customtools/strings.o

o/usr/bin/ascii: init_outdir customtools/ascii.c
	$(CC) $(CFLAGS) -o o/usr/bin/ascii customtools/ascii.c

util-linux/rev.o: util-linux/rev.c
	$(CC) $(CFLAGS) -c -o util-linux/rev.o util-linux/rev.c

o/usr/bin/rev: init_outdir lib/prettyprint.o util-linux/rev.o
	$(LD) $(LDFLAGS) -o o/usr/bin/rev lib/prettyprint.o util-linux/rev.o

o/usr/sbin/nologin: init_outdir util-linux/nologin.c
	$(CC) $(CFLAGS) -o o/usr/sbin/nologin util-linux/nologin.c

util-linux/uuidgen.o: util-linux/uuidgen.c
	$(CC) $(CFLAGS) -c -o util-linux/uuidgen.o util-linux/uuidgen.c

# requires libsodium
o/usr/bin/uuidgen: init_outdir lib/prettyprint.o lib/util.o util-linux/uuidgen.o
	$(LD) $(LDFLAGS) -o o/usr/bin/uuidgen lib/prettyprint.o lib/util.o util-linux/uuidgen.o -lsodium

findutils/xargs.o: findutils/xargs.c
	$(CC) $(CFLAGS) -c -o findutils/xargs.o findutils/xargs.c

o/usr/bin/xargs: init_outdir lib/prettyprint.o findutils/xargs.o
	$(LD) $(LDFLAGS) -o o/usr/bin/xargs lib/prettyprint.o findutils/xargs.o

customtools/rng.o: customtools/rng.c
	$(CC) $(CFLAGS) -c -o customtools/rng.o customtools/rng.c

# requires libsodium
o/usr/bin/rng: init_outdir lib/prettyprint.o lib/util.o customtools/rng.o
	$(LD) $(LDFLAGS) -o o/usr/bin/rng lib/prettyprint.o lib/util.o customtools/rng.o -lsodium

customtools/exedump.o: customtools/exedump.c config.h
	$(CC) $(CFLAGS) -c -o customtools/exedump.o customtools/exedump.c

o/usr/bin/exedump: init_outdir lib/prettyprint.o lib/util.o customtools/exedump.o
	$(LD) $(LDFLAGS) -o o/usr/bin/exedump lib/prettyprint.o lib/util.o customtools/exedump.o -lm

customtools/usleep.o: customtools/usleep.c
	$(CC) $(CFLAGS) -c -o customtools/usleep.o customtools/usleep.c

o/usr/bin/usleep: init_outdir lib/prettyprint.o lib/util.o customtools/usleep.o
	$(LD) $(LDFLAGS) -o o/usr/bin/usleep lib/prettyprint.o lib/util.o customtools/usleep.o

procutils/w.o: procutils/w.c
	$(CC) $(CFLAGS) -c -o procutils/w.o procutils/w.c

o/usr/bin/w: init_outdir lib/prettyprint.o lib/util.o lib/util_m.o procutils/w.o
	$(LD) $(LDFLAGS) -o o/usr/bin/w -lm lib/prettyprint.o lib/util.o lib/util_m.o procutils/w.o

coreutils/whoami.o: coreutils/whoami.c
	$(CC) $(CFLAGS) -c -o coreutils/whoami.o coreutils/whoami.c

o/usr/bin/whoami: init_outdir lib/prettyprint.o coreutils/whoami.o
	$(LD) $(LDFLAGS) -o o/usr/bin/whoami lib/prettyprint.o coreutils/whoami.o

coreutils/tty.o: coreutils/tty.c
	$(CC) $(CFLAGS) -c -o coreutils/tty.o coreutils/tty.c

o/usr/bin/tty: init_outdir coreutils/tty.o
	$(LD) $(LDFLAGS) -o o/usr/bin/tty coreutils/tty.o

coreutils/test.o: coreutils/test.c
	$(CC) $(CFLAGS) -c -o coreutils/test.o coreutils/test.c

o/bin/test: init_outdir lib/prettyprint.o coreutils/test.o
	$(LD) $(LDFLAGS) -o o/bin/test lib/prettyprint.o coreutils/test.o

coreutils/uniq.o: coreutils/uniq.c
	$(CC) $(CFLAGS) -c -o coreutils/uniq.o coreutils/uniq.c

o/usr/bin/uniq: init_outdir lib/prettyprint.o lib/util.o coreutils/uniq.o
	$(LD) $(LDFLAGS) -o o/usr/bin/uniq lib/prettyprint.o lib/util.o coreutils/uniq.o

coreutils/mkdir.o: coreutils/mkdir.c
	$(CC) $(CFLAGS) -c -o coreutils/mkdir.o coreutils/mkdir.c

o/bin/mkdir: init_outdir lib/prettyprint.o lib/util.o coreutils/mkdir.o
	$(LD) $(LDFLAGS) -o o/bin/mkdir lib/prettyprint.o lib/util.o coreutils/mkdir.o

coreutils/rmdir.o: coreutils/rmdir.c
	$(CC) $(CFLAGS) -c -o coreutils/rmdir.o coreutils/rmdir.c

o/bin/rmdir: init_outdir lib/prettyprint.o coreutils/rmdir.o
	$(LD) $(LDFLAGS) -o o/bin/rmdir lib/prettyprint.o coreutils/rmdir.o

coreutils/head.o: coreutils/head.c
	$(CC) $(CFLAGS) -c -o coreutils/head.o coreutils/head.c

o/usr/bin/head: init_outdir lib/prettyprint.o lib/util.o coreutils/head.o
	$(LD) $(LDFLAGS) -o o/usr/bin/head lib/prettyprint.o lib/util.o coreutils/head.o

coreutils/tail.o: coreutils/tail.c
	$(CC) $(CFLAGS) -c -o coreutils/tail.o coreutils/tail.c

o/usr/bin/tail: init_outdir lib/prettyprint.o lib/util.o coreutils/tail.o
	$(LD) $(LDFLAGS) -o o/usr/bin/tail lib/prettyprint.o lib/util.o coreutils/tail.o

customtools/clear.o: customtools/clear.c
	$(CC) $(CFLAGS) -c -o customtools/clear.o customtools/clear.c

o/usr/bin/clear: init_outdir customtools/clear.o
	$(LD) $(LDFLAGS) -o o/usr/bin/clear customtools/clear.o

clean:
	rm -rf o/* coreutils/*.o customtools/*.o diffutils/*.o findutils/*.o grep/*.o gzip/*.o iconv/*.o lib/*.o patch/*.o procutils/*.o sed/*.o sharutils/*.o su/*.o util-linux/*.o which/*.o passwdutils/*.o

check:
	find -name '*.c' -or -name '*.h' | xargs cppcheck --std=c99 --check-level=exhaustive

init_outdir: o/bin o/sbin o/usr/bin o/usr/sbin

o/bin:
	mkdir -p $@

o/sbin:
	mkdir -p $@

o/usr/bin:
	mkdir -p $@

o/usr/sbin:
	mkdir -p $@

.PHONY: clean all init_outdir install check
