#!/bin/sh


[ -z "$PREFIX" ] && PREFIX="/usr/local" # safeguard in case PREFIX is not in config.mk
[ -z "$DESTDIR" ] && DESTDIR="" # not needed, only for readability

set -ex

mkdir -pv o/share/man/man1
cp -v docs/*.1 o/share/man/man1/
# mkdir -pv o/share/man/man8
# cp -v docs/*.8 o/share/man/man8/

_dest_dir="$DESTDIR"/"$PREFIX"
mkdir -pv $_dest_dir
cp -rv o/* "$_dest_dir"/
{ set +x; } 2>/dev/null
