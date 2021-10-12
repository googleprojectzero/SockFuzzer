#!/bin/sh

set -e

run()
{
  echo "$@"
  "$@"
}

incdir="${top_srcdir}/include"

for inc in $(cd $incdir; find -name '*.h' | sort | cut -c3-); do
  cat >headers-system-gen.c <<SOURCE
#include <$inc>
int main() { return 0; }
SOURCE

  echo "testing header $inc"
  run $CC -isystem "$incdir" $CPPFLAGS headers-system-gen.c -o /dev/null
  echo

  rm -f headers-system-gen.*
done
