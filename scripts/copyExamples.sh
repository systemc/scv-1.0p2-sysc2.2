#!/bin/sh -h

# copyExamples.sh <srcdir> <dstdir>

# Skips CVS directories, recurses through
# directories, copies only certain file
# types.

# By checking "dstdir != srcdir/f" I'm
# insuring against a nasty recursion
# that would happen when build=install,
# since I'd copy examples -> examples/scv.
# This check doesn't prevent an indirect
# recursion.

srcdir=$1
dstdir=$2

srcdir=`cd $srcdir;pwd`
mkdir -p $dstdir
dstdir=`cd $dstdir;pwd`

scripts=`dirname $0`
scripts=`cd $scripts; pwd`

if test "$srcdir" != "$dstdir"; then

  cd $srcdir

  isleaf="yes"
  for f in *; do
    if test -d $f -a $f != "CVS" -a $dstdir != $srcdir/$f; then
      $scripts/copyExamples.sh $srcdir/$f $dstdir/$f
      isleaf="no"
    fi
  done
  for f in *[chp] *.v* *.tcl README; do
    if test -r $f; then
      rm -f $dstdir/$f
      cp $f $dstdir
      chmod u+w $dstdir/$f
    fi
  done
  # only copy Makefile in leaf dirs
  if test -r Makefile -a $isleaf = "yes"; then
    rm -f $dstdir/Makefile
    cp Makefile $dstdir
    chmod u+w $dstdir/Makefile
  fi

fi
