#!/bin/sh

md5_prog="md5"
[ "$GNU_MODE" = "1" ] && {
  md5_prog="md5sum"
}

[ $# -eq 0 ] && {
  echo "usage: $0 file1 [file2] ..." 1>&2
  exit 1
}

cat << EOF
# This is a shell archive.  Save it in a file, remove anything before
# this line, and then unpack it by entering "sh file".  Note, it may
# create directories; files and directories will be owned by you and
# have default permissions.
#
# This archive contains:
#
EOF

for i
do
  echo "# $i"
done
echo "#"

for i
do
	if [ -d "$i" ]; then
		echo "echo c - $i"
		echo "mkdir -p $i > /dev/null 2>&1"
	else
    md5sum="$(printf %s "$i" | "$md5_prog")"
		echo "echo x - $i"
		echo "sed 's/^X//' >$i << '$md5sum'"
		sed 's/^/X/' "$i" || exit
		echo "$md5sum"
	fi
done
echo exit
echo ""

exit 0
