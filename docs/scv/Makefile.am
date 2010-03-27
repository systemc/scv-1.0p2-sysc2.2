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

SUBDIRS = scvref

AUTOMAKE_OPTIONS = foreign

CLEANFILES = ChangeLog README LICENSE

DISTCLEANFILES = ${CLEANFILES}

copyFiles = ${top_builddir}/scripts/copyFiles.sh

all : all-recursive
	${copyFiles} -s ${top_srcdir} . ChangeLog README LICENSE

@dummy_install@ :
	@echo "Build directory and install directory are the same."
	@echo "No install is necessary."

@actual_install@ :
	${copyFiles} ${top_srcdir} ${prefix}/docs/scv ChangeLog README LICENSE
	${copyFiles} ${srcdir} ${prefix}/docs/scv \
		date03a2.pdf intro_slides.pdf scv_random_white_paper4.pdf

dist-hook :
	mkdir -p ${distdir}
	-if test -f ${pdfDocSrcDir}/date03a2.pdf; then \
	  cp ${pdfDocSrcDir}/date03a2.pdf ${distdir}; \
	fi
	-if test -f ${pdfDocSrcDir}/intro_slides.pdf; then \
	  cp ${pdfDocSrcDir}/intro_slides.pdf ${distdir}; \
	fi
	-if test -f ${pdfDocSrcDir}/scv_random_white_paper4.pdf; then \
	  cp ${pdfDocSrcDir}/scv_random_white_paper4.pdf ${distdir}; \
	fi
	-if test -f ${srcdir}/date03a2.pdf; then \
	  cp ${srcdir}/date03a2.pdf ${distdir}; \
	fi
	-if test -f ${srcdir}/intro_slides.pdf; then \
	  cp ${srcdir}/intro_slides.pdf ${distdir}; \
	fi
	-if test -f ${srcdir}/scv_random_white_paper4.pdf; then \
	  cp ${srcdir}/scv_random_white_paper4.pdf ${distdir}; \
	fi
