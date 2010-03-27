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

SUBDIRS = \
	scripts \
	src \
	docs \
	examples

AUTOMAKE_OPTIONS = foreign

copyFiles = ${top_builddir}/scripts/copyFiles.sh

TEXTDOCS = LICENSE README AUTHORS COPYING INSTALL NEWS RELEASENOTES

EXTRA_DIST = ${TEXTDOCS} kitnumber.txt majorrev.txt minorrev.txt \
        kittype.txt relnumber.txt osci_issues_for_scv.txt

scv_config.h : config.h
	cp config.h scv_config.h
	echo "#undef PACKAGE" >>scv_config.h
	mkdir -p ${buildInc}/scv
	( HOLD=`pwd`; cd ${buildInc}/scv; rm -f scv_config.h; ln -s $$HOLD/scv_config.h . )

debug:
	$(MAKE) all CXXFLAGS="$(CXXFLAGS_DEBUG)" CFLAGS="$(CFLAGS_DEBUG)"

opt:
	$(MAKE) all CXXFLAGS="$(CXXFLAGS_OPT)" CFLAGS="$(CFLAGS_OPT)"

all : scv_config.h
	$(MAKE) $(AM_MAKEFLAGS) all-recursive

clean : clean-recursive
	-rm -rf ${buildBin} ${buildInc} ${buildLib} scv_config.h

distclean : distclean-recursive
	-rm -rf ${buildBin} ${buildInc} ${buildLib} scv_config.h config.status

@actual_install@ : scv_config.h
	${copyFiles} . ${includedir}/scv scv_config.h
	for f in ${TEXTDOCS}; do cp ${srcdir}/$$f ${prefix}/$$f.scv; done
	for f in ${TEXTDOCS}; do chmod u+w ${prefix}/$$f.scv; done

uninstall : uninstall-recursive
	for f in ${TEXTDOCS}; do rm -f ${prefix}/$$f.scv; done
	-rm -rf ${prefix}/docs/scv ${prefix}/examples/scv ${prefix}/include/scv

dist-hook :
	mkdir -p ${distdir}
	rm -rf ${distdir}/msvc71
	cp -r ${srcdir}/msvc71 ${distdir}
