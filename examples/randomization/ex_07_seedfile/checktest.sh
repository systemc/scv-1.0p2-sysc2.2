#! /bin/sh

LOGFILE1=$1
LOGFILE2=$2
GOLDENLOGPREFIX=$3

GOLDENLOGFILE1=${GOLDENLOGPREFIX}1.au
GOLDENLOGFILE2=${GOLDENLOGPREFIX}2.au
DIFFFILE="logfile.diff"
TMPFILE="logfile.grep"

if [ ! -f $LOGFILE1 ] || [ ! -f $LOGFILE2 ] || [ ! -f $GOLDENLOGFILE1 ] || [ ! -f $GOLDENLOGFILE2 ] ; then
    echo "fail - missing $LOGFILE1, $LOGFILE2, $GOLDENLOGFILE1 or $GOLDENLOGFILE2"
    exit
fi
grep "^%%REG: " $LOGFILE1 >$TMPFILE
if [ ! -f $TMPFILE ] ; then
    echo "fail - missing $TMPFILE"
    exit
fi
diff $TMPFILE $GOLDENLOGFILE1 >$DIFFFILE
rm $TMPFILE
if [ -s $DIFFFILE ] ; then
    echo "fail"
    exit
fi
grep "^%%REG: " $LOGFILE2 >$TMPFILE
if [ ! -f $TMPFILE ] ; then
    echo "fail - missing $TMPFILE"
    exit;
fi
diff $TMPFILE $GOLDENLOGFILE2 >$DIFFFILE
rm $TMPFILE
if [ -s $DIFFFILE ] ; then
    echo "fail"
else
    echo "passed"
fi
