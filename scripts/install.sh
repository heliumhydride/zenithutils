#!/bin/sh

if [ -z "$1" ]; then
  PREFIX="/"
else
  PREFIX="$1"
fi

[ -z "$2" ] || DESTDIR="$2"

set +x 
mkdir -pv o/usr/share/man/man1
cp -v docs/*.1 o/usr/share/man/man1/
# mkdir -pv o/usr/share/man/man8
# cp -v docs/*.8 o/usr/share/man/man8/

_dest_dir="$DESTDIR"/"$PREFIX"
[ -e "$_destdir" ] || mkdir -pv $_dest_dir
cp -rv o/* "$_dest_dir"/
{ set +x; } 2>/dev/null
