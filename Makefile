include config.mk

all: customtools coreutils util-linux which procutils diffutils findutils grep gzip iconv patch sed sharutils su passwdutils

customtools: config.h init_outdir
	$(MAKE) -C customtools

coreutils: config.h init_outdir
	$(MAKE) -C coreutils

util-linux: config.h init_outdir
	$(MAKE) -C util-linux

which: config.h init_outdir
	$(MAKE) -C which

procutils: config.h init_outdir
	$(MAKE) -C procutils

diffutils: config.h init_outdir
	$(MAKE) -C diffutils

findutils: config.h init_outdir
	$(MAKE) -C findutils

grep: config.h init_outdir
	$(MAKE) -C grep

gzip: config.h init_outdir
	$(MAKE) -C gzip

iconv: config.h init_outdir
	$(MAKE) -C iconv

patch: config.h init_outdir
	$(MAKE) -C patch

sed: config.h init_outdir
	$(MAKE) -C sed

sharutils: config.h init_outdir
	$(MAKE) -C sharutils

su: config.h init_outdir
	$(MAKE) -C su

passwdutils: config.h init_outdir
	$(MAKE) -C passwdutils

config.h: config.def.h
	cp config.def.h config.h

init_outdir: o/bin o/sbin

o/bin:
	mkdir -p $@

o/sbin:
	mkdir -p $@

install: init_outdir
	PREFIX="$(PREFIX)" DESTDIR="$(DESTDIR)" scripts/install.sh

clean:
	rm -rf o/* coreutils/*.o customtools/*.o diffutils/*.o findutils/*.o grep/*.o gzip/*.o iconv/*.o lib/*.o patch/*.o procutils/*.o sed/*.o sharutils/*.o su/*.o util-linux/*.o which/*.o passwdutils/*.o config.h

check:
	find -name '*.c' -or -name '*.h' | xargs cppcheck --std=c99 --check-level=exhaustive

tags:
	ctags -R --c-kinds=+p --exclude=TODO --exclude=docs --exclude=o --exclude=scripts --exclude=README.md

.PHONY: clean all init_outdir install check tags
