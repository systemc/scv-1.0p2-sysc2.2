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
lib_LTLIBRARIES = libscv.la

library_includedir = $(prefix)/include/scv
##
## Get definition of libscv_cxx_files.  This list can't be defined in configure because the _SOURCES
## variable gets processed by automake before configure runs.
##
include $(top_srcdir)/src/scv/Makefile.extra

libscv_la_SOURCES = ${libscv_cxx_files}
EXTRA_DIST = Makefile.extra

library_include_HEADERS = \
_scv_associative_array.h \
_scv_ext_callbacks.h \
_scv_data_structure.h \
_scv_ext_comp.h \
_scv_ext_rw.h \
_scv_ext_type.h \
_scv_ext_util.h \
_scv_ext_rand.h \
_scv_introspection.h \
_scv_list_iter.h \
_scv_randomization.h \
_scv_smart_ptr.h \
scv_bag.h \
scv_constraint.h \
scv_constraint_range.h \
scv_debug.h \
scv_expression.h \
scv_introspection.h \
scv_messages.h \
scv_object_if.h \
scv_random.h \
scv_report.h \
scv_shared_ptr.h \
scv_sparse_array.h \
scv_tr.h \
scv_util.h \
scv_kit_date.h

INCLUDES = \
	-I${buildInc} \
	-I${top_srcdir}/src \
	-I${top_srcdir}/src/cudd/2.3.0/cudd \
	-I${top_srcdir}/src/cudd/2.3.0/obj \
	-I${top_srcdir}/src/cudd/2.3.0/util \
	-I${top_srcdir}/src/cudd/2.3.0/mtr \
	-I${top_srcdir}/src/cudd/2.3.0/st \
	-I${SYSC_INC_PREFIX} \
	-DSCV_VERSION=\"$(VERSION)\"

libscv_la_LIBADD= \
	../cudd/2.3.0/obj/libobj.la \
	../cudd/2.3.0/cudd/libcudd.la \
	../cudd/2.3.0/util/libutil.la \
	../cudd/2.3.0/mtr/libmtr.la \
	../cudd/2.3.0/st/libst.la


SYSC_LIBRARY = ${SYSC_LIB_PREFIX}/libsystemc.a

libscv_la_LDFLAGS = -version-info 0:0:0

