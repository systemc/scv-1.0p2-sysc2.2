//  -*- C++ -*- <this line is for emacs to recognize it as C++ code>
/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2002 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.3 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  scv_util.h --
  The public interface for various small facilities.

  Original Authors (Cadence Design Systems, Inc):
  Norris Ip, Dean Shea, John Rose, Jasvinder Singh, William Paulsen,
  John Pierce, Rachida Kebichi, Ted Elkind, David Bailey
  2002-09-23

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#ifndef SCV_UTIL_H
#define SCV_UTIL_H

#include "scv/scv_config.h"

#ifdef SCV_USE_IOSTREAM_H
# include <iostream.h>
#else
# include <iostream>
#endif

#include <string>

#include "systemc.h"

#ifdef _USE_UINT64_WRITE
inline ostream& operator<<(ostream& os, const unsigned long long& full) {
  char image[32];
  sprintf(image,"%llu",full);
  return os << image;
}
#endif


int _scv_make_unique_id(const string& name, const string& kind);
const string _scv_make_unique_name(const string& name, int id);


//
// process name
//

#if !( defined SYSTEMC_VERSION ) || ( SYSTEMC_VERSION < 20060204 )

typedef const char *(_scv_process_name_server_t)(sc_process_b *proc_p);
extern _scv_process_name_server_t *_scv_process_name_server;
void _scv_set_process_name_server(_scv_process_name_server_t *);
const char *_scv_get_process_name(const sc_process_b *proc_p);

const char *scv_get_process_name(sc_process_b *proc_p);

#else //SystemC 2.2

typedef const char *(_scv_process_name_server_t)(sc_process_handle proc_p);
extern _scv_process_name_server_t *_scv_process_name_server;
void _scv_set_process_name_server(_scv_process_name_server_t *);
const char *_scv_get_process_name(const sc_process_handle proc_p);

const char *scv_get_process_name(sc_process_handle proc_p);

#endif // !( defined SYSTEMC_VERSION ) || ( SYSTEMC_VERSION < 20060204 )


//
// scv_startup
//

#define SCV_STARTUP() { \
  static bool dummy = scv_startup(); \
  if (0) cout << dummy << endl; \
}

bool scv_startup();

//
// scv_out
//

extern ostream *_scv_out_p;
#define scv_out (*_scv_out_p)

// Keep for backward compatibility
//
// tb_status (for regression convenience)
//
#define tb_status cout
#define TBS_INFO "%%TB_STATUS_INFO: "
#define TBS_WARNING "%%TB_STATUS_WARNING: "
#define TBS_ERROR "%%TB_STATUS_ERROR: "
#define TBS_SUCCESS "%%TB_STATUS_SUCCESS: "
#define TBS_FAIL "%%TB_STATUS_FAIL: "

#endif
