#!/bin/sh

[ -z "$PREFIX" ] && PREFIX="/usr/local"
[ -z "$DESTDIR" ] && DESTDIR=""

set +x 
mkdir -pv o/share/man/man1
cp -v docs/*.1 o/share/man/man1/
# mkdir -pv o/share/man/man8
# cp -v docs/*.8 o/share/man/man8/

_dest_dir="$DESTDIR"/"$PREFIX"
[ -e "$_destdir" ] || mkdir -pv $_dest_dir
cp -rv o/* "$_dest_dir"/
{ set +x; } 2>/dev/null
