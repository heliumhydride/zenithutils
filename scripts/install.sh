#!/bin/sh

[ -z "$PREFIX" ] && PREFIX="/usr/local" # safeguard in case PREFIX is not in config.mk

_dest_dir="$DESTDIR"/"$PREFIX"
set -ex

mkdir -pv "$_dest_dir"
cp -rv o/* "$_dest_dir"/

{ set +x; } 2>/dev/null
