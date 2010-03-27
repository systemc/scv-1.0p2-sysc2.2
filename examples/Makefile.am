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

##  Process this file with automake to produce Makefile.in

SHELL = /bin/sh
EXTRA_DIST = Makefile.rules.in README

AUTOMAKE_OPTIONS = foreign

copyExamples = ${top_srcdir}/scripts/copyExamples.sh

all : all-am
	echo SYSC_INC_PREFIX = ${SYSC_INC_PREFIX} >Makefile.rules; \
	echo SYSC_LIB_PREFIX = ${SYSC_LIB_PREFIX} >>Makefile.rules; \
	echo includedir = ${buildInc} >>Makefile.rules; \
	echo libdir = ${buildLib} >>Makefile.rules; \
	cat ${srcdir}/Makefile.rules.in >>Makefile.rules
	if test -n "${extraExamples}" -a -d "${extraExamples}"; then \
	  cp -rf ${extraExamples}/* .; \
	fi
	${copyExamples} ${srcdir} .

clean-worker :
	-rm -rf Makefile.rules
	SRC=`cd ${srcdir};pwd`; BLD=`pwd`; \
	if test "$$SRC" != "$$BLD"; then rm -rf [^M]*; fi

clean : clean-am clean-worker 

distclean : distclean-am clean-worker

install :
	mkdir -p ${prefix}/examples/scv
	rules=${prefix}/examples/scv/Makefile.rules; \
	echo SYSC_INC_PREFIX = ${SYSC_INC_PREFIX} >$$rules; \
	echo SYSC_LIB_PREFIX = ${SYSC_LIB_PREFIX} >>$$rules; \
	echo includedir = ${includedir} >>$$rules; \
	echo libdir = ${libdir} >>$$rules; \
	cat ${srcdir}/Makefile.rules.in >>$$rules
	if test -n "${extraExamples}" -a -d "${extraExamples}"; then \
	  cp -rf ${extraExamples}/* ${prefix}/examples/scv; \
	fi
	${copyExamples} ${srcdir} ${prefix}/examples/scv

dist-hook :
	if test -n "${extraExamples}" -a -d "${extraExamples}"; then \
	  cp -rf ${extraExamples}/* ${distdir}; \
	fi
	${copyExamples} ${srcdir} ${distdir}
