include ../config.mk

# do we really need 'rename' and 'hardlink' ? (see 'mv' and 'ln')
# agetty not implemented, see nyagetty from chimera linux
# hwclock not being implemented for now
# losetup, pivot_root, ionice, write, show a "does not apply to windows" and return 1
# for mkswap/swapon/swapoff on windows: do we have functions in the win32 api to change pagefile settings ?
# for login on windows: use as a frontend to LogonUI/runas.exe maybe ? kind of a strech but I don't see what else login.exe would do...
# fsck on windows: do we just 'execvp("chkdsk.exe", ...);' ?

# TODO note to self: nologin, fdisk, fsck, losetup, mkfs, mkswap, mount, pivot_root are in /sbin.
PROGS=rev nologin uuidgen lscpu column blkid cal cfdisk chsh col dmesg eject fallocate fdisk findfs fsck getopt hexdump ionice last login losetup lsblk lslogins mcookie mkfs mkswap more mount mountpoint pivot_root renice write whereis swapon swapoff

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rev: rev.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

nologin: nologin.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

# requires libsodium
uuidgen: uuidgen.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -lsodium -o ../o/bin/$@

