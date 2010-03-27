/*
 * The following code is derived, directly or indirectly, from the SystemC
 * source code Copyright (c) 1996-2002 by all Contributors.
 * All Rights reserved.
 *
 * The contents of this file are subject to the restrictions and limitations
 * set forth in the SystemC Open Source License Version 2.3 (the "License");
 * You may not use this file except in compliance with such restrictions and
 * limitations. You may obtain instructions on how to receive a copy of the
 * License at http://www.systemc.org/. Software distributed by Contributors
 * under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
 * ANY KIND, either express or implied. See the License for the specific
 * language governing rights and limitations under the License.
 */

 
/* Define if we're on Linux */
#undef ARCH_IS_X86

/* the full canonical system: cpu, vendor, os */
#undef TARGET

/* found Dl_info in dlfcn.h */
#undef HAVE_DL_INFO

/* A string that contains the shared library extention (e.g. .so or .sl) */
#undef SHLIB_EXT

/* Define if we're on the HP-UX 11 */
#undef RWSTD_MULTI_THREAD 
#undef RW_MULTI_THREAD 
#undef _REENTRANT
#undef __HPACC_THREAD_SAFE_RB_TREE 
#undef HP_THREAD_SAFE 
#undef _THREAD_SAFE
#undef _POSIX_C_SOURCE
#undef hp_hpux11

#undef _USE_FMTFLAGS_TYPE
#undef _USE_FRIEND_FOR_EQUAL
#undef _USE_EXPLICIT_NEQ
#undef _USE_HASH_MAP
#undef _USE_PADDING_ON_STRUCTS
#undef _USE_UINT64_WRITE

#undef SCV_USE_IOSTREAM_H
#undef _SCV_USE_SC_REPORT

#undef SC_VERSION
@BOTTOM@

#ifdef __cplusplus

/* cc on HPUX seems to define this automatically so avoid redefinition warnings by */
/* conditionally defining it. */
#undef _HPUX_SOURCE

#if defined (__SUNPRO_CC)
#include<list>
#include<map>
#include<string>
#endif

/* HP-UX's aCC doesn't have std defined until it sees a std lib header file */
/* (unlike g++ and SunWorks CC.) */
/* So define it here empty.  Namespaces are extensible, so this is harmless. */
namespace std {}
using namespace std;

#ifdef DELETE
#undef DELETE
#endif
#ifdef ERROR
#undef ERROR
#endif

#endif // __cplusplus

#if defined (__SUNPRO_CC)
  using std::list;
  using std::pair;
  using std::map;
  using std::less;
  using std::string;
  using std::equal_to;
#endif

#if defined(_MSC_VER)
# define _USE_FMTFLAGS_TYPE
# define _USE_FRIEND_FOR_EQUAL
# define _USE_EXPLICIT_NEQ
# define SC_VERSION 2000001
# define HAVE_STDDEF_H
#endif
