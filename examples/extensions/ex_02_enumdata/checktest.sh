#! /bin/sh

LOGFILE=$1
GOLDENLOGFILE=$2
DIFFFILE="logfile.diff"
TMPFILE="logfile.grep"

if [ ! -f "$LOGFILE" ] || [ ! -f "$GOLDENLOGFILE" ] ; then
    echo "fail"
    exit;
fi
grep "^%%REG: " $LOGFILE >$TMPFILE
if [ ! -f $TMPFILE ] ; then
    echo "fail"
    exit;
fi
diff $TMPFILE $GOLDENLOGFILE >$DIFFFILE
rm $TMPFILE
if [ -s $DIFFFILE ] ; then
    echo "fail"
else
    echo "passed"
fi
