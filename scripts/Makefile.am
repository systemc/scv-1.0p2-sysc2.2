## ****************************************************************************
##
##  The following code is derived, directly or indirectly, from the SystemC
##  source code Copyright (c) 1996-2002 by all Contributors.
##  All Rights reserved.
##
##  The contents of this file are subject to the restrictions and limitations
##  set forth in the SystemC Open Source License Version 2.3 (the "License");
##  You may not use this file except in compliance with such restrictions and
##  limitations. You may obtain instructions on how to receive a copy of the
##  License at http://www.systemc.org/. Software distributed by Contributors
##  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
##  ANY KIND, either express or implied. See the License for the specific
##  language governing rights and limitations under the License.
##  
## ****************************************************************************
##
##  Makefile.am --
##  Process this file with automake to produce a Makefile.in file.
## 
## ****************************************************************************
##
##  Original Authors:
##  Norris Ip, Dean Shea, John Rose, Jasvinder Singh, William Paulsen,
##  John Pierce, Rachida Kebichi, Ted Elkind, David Bailey,
##  Cadence Design Systems, Inc., 2002-09-23
##
## ****************************************************************************
##  
##  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
##  changes you are making here.
##
##      Name, Affiliation, Date:
##  Description of Modification:
##
## ****************************************************************************

SHELL = /bin/sh
AUTOMAKE_OPTIONS = foreign
EXTRA_DIST = \
	copyDir.sh.in copyExamples.sh copyFiles.sh.in

all : all-am create_copiers

create_copiers :
	# create copyDir.sh
	echo "#!/bin/sh -h" >copyDir.sh
	echo "overwrite=${overwrite_files}" >>copyDir.sh
	cat ${srcdir}/copyDir.sh.in >>copyDir.sh
	# create copyExamples.sh
	if test ! -r copyExamples.sh; then \
	  cp ${srcdir}/copyExamples.sh .; \
	fi
	# create copyFiles.sh
	echo "#!/bin/sh -h" >copyFiles.sh
	echo "overwrite=${overwrite_files}" >>copyFiles.sh
	cat ${srcdir}/copyFiles.sh.in >>copyFiles.sh
	# set permissions
	chmod a+x copyDir.sh copyFiles.sh

clean-worker :
	-rm -rf copyDir.sh copyFiles.sh
	SRC=`cd ${srcdir};pwd`; BLD=`pwd`; \
	if test "$$SRC" != "$$BLD"; then rm -f copyExamples.sh; fi

clean : clean-am clean-worker

distclean : distclean-am clean-worker

@dummy_install@ :
	@echo "Build directory and install directory are the same."
	@echo "No install is necessary."

@actual_install@ : 
	mkdir -p ${includedir} ${libdir}

dist-hook : create_copiers
