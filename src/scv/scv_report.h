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

  scv_report.h --  The public interface for error messages.

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

#ifndef _SCV_REPORT_H
#define _SCV_REPORT_H

#include "scv/scv_config.h"


#ifdef _SCV_USE_SC_REPORT

typedef sc_actions scv_actions;
typedef sc_report scv_report;
typedef sc_report_handler scv_report_handler;
typedef sc_severity scv_severity;
typedef const char *scv_msg_type;

#define SCV_INFO SC_INFO
#define SCV_WARNING SC_WARNING
#define SCV_ERROR SC_ERROR
#define SCV_FATAL SC_FATAL

#define SCV_UNSPECIFIED SC_UNSPECIFIED
#define SCV_DO_NOTHING SC_DO_NOTHING
#define SCV_THROW SC_THROW
#define SCV_LOG SC_LOG
#define SCV_DISPLAY SC_DISPLAY
#define SCV_CACHE_REPORT SC_CACHE_REPORT
#define SCV_INTERRUPT SC_INTERRUPT
#define SCV_STOP SC_STOP
#define SCV_ABORT SC_ABORT

#define SCV_DEFAULT_INFO_ACTIONS SC_DEFAULT_INFO_ACTIONS
#define SCV_DEFAULT_WARNING_ACTIONS SC_DEFAULT_WARNING_ACTIONS
#define SCV_DEFAULT_ERROR_ACTIONS SC_DEFAULT_ERROR_ACTIONS
#define SCV_DEFAULT_FATAL_ACTIONS SC_DEFAULT_FATAL_ACTIONS

#define SCV_REPORT_INFO SC_REPORT_INFO
#define SCV_REPORT_WARNING SC_REPORT_WARNING
#define SCV_REPORT_ERROR SC_REPORT_ERROR
#define SCV_REPORT_FATAL SC_REPORT_FATAL

#else


#include <string>

#include "scv/scv_object_if.h"
#include "scv/scv_util.h"
#include "scv/scv_debug.h"

#ifdef set_handler
# undef set_handler
#endif

#ifdef _MSC_VER
#ifdef DELETE
#undef DELETE
#endif
#ifdef ERROR
#undef ERROR
#endif
#endif


//
// scv_report
//


#define SCV_REPORT_INFO(msg_type,msg) \
   scv_report_handler::report(SCV_INFO,(msg_type),(msg),__FILE__,__LINE__)

#define SCV_REPORT_WARNING(msg_type,msg) \
   scv_report_handler::report(SCV_WARNING,(msg_type),(msg),__FILE__,__LINE__)

#define SCV_REPORT_ERROR(msg_type,msg) \
   scv_report_handler::report(SCV_ERROR,(msg_type),(msg),__FILE__,__LINE__)

#define SCV_REPORT_FATAL(msg_type,msg) \
   scv_report_handler::report(SCV_FATAL,(msg_type),(msg),__FILE__,__LINE__)


enum scv_severity {
   SCV_INFO = 0,        // informative only
   SCV_WARNING, // indicates potentially incorrect condition
   SCV_ERROR,   // indicates a definite problem
   SCV_FATAL    // indicates a problem from which we cannot recover
};


typedef unsigned scv_actions;

const scv_actions SCV_UNSPECIFIED  = 0x0000; // look for lower-priority rule
const scv_actions SCV_DO_NOTHING   = 0x0001; // take no action (ignore if other bits set)
const scv_actions SCV_THROW        = 0x0002; // throw an exception
const scv_actions SCV_LOG          = 0x0004; // add report to report log
const scv_actions SCV_DISPLAY      = 0x0008; // display report to screen
const scv_actions SCV_CACHE_REPORT = 0x0010; // save report to cache
const scv_actions SCV_INTERRUPT    = 0x0020; // interrupt simulation
const scv_actions SCV_STOP         = 0x0040; // call sc_stop()
const scv_actions SCV_ABORT        = 0x0080; // call abort(0)


typedef const char *scv_msg_type;


class scv_report : public scv_object_if {
public:

   scv_report(
     scv_severity severity, scv_msg_type msg_type,
     const char *msg,
     const char *file_name, int line_number,
     sc_time time, const char *_process_name
   );

   scv_report(const scv_report&);

   virtual ~scv_report() {}

   scv_report& operator=(const scv_report&);

   // for use with sc_exception
   operator const char *() const;

   scv_severity get_severity() const
     { return _severity; }
   scv_msg_type get_msg_type() const
     { return _msg_type.c_str(); }
   const char *get_msg() const
     { return _msg.c_str(); }
   const char *get_file_name() const
     { return _file_name.c_str(); }
   int get_line_number() const
     { return _line_number; }

   sc_time get_time() const
     { return _time; }
   const char *get_process_name() const
     { return _process_name.c_str(); }

   const char *get_name() const
     { return _msg_type.c_str(); }
   const char *kind() const
     { return _kind; }
   void print(ostream& o=cout, int details=0, int indent=0) const;

private:

   scv_severity _severity;
   string _msg_type;
   string _msg;
   string _file_name;
   int _line_number;
   sc_time _time;
   string _process_name;

   static const char *_kind;
};


class scv_report_handler {
public:

   scv_report_handler() {}
   virtual ~scv_report_handler() {}

   //
   // configure reporting facility
   //

   // specify handler for reports
   // 0 restores default 
   static void set_handler(
     void (*handler)(const scv_report&, const scv_actions&) = 0
   );

   // specify actions to take for messages
   // SCV_UNSPECIFIED restores default
   static scv_actions set_actions(
     scv_severity severity,
     scv_actions actions = SCV_UNSPECIFIED
   );
   static scv_actions set_actions(
     scv_msg_type msg_type,
     scv_actions actions = SCV_UNSPECIFIED
   );
   static scv_actions set_actions(
     scv_msg_type msg_type, scv_severity severity,
     scv_actions actions = SCV_UNSPECIFIED
   );

   // specify how many occurrences to tolerate
   // -1 restores default
   static int stop_after(
     scv_severity severity,
     int limit = -1
   );
   static int stop_after(
     scv_msg_type msg_type,
     int limit = -1
   );
   static int stop_after(
     scv_msg_type msg_type, scv_severity severity,
     int limit = -1
   );

   // override configured actions
   static scv_actions suppress(scv_actions actions = 0U);
   static scv_actions force(scv_actions actions = 0U);

   // add callback
   static void register_cb(void (*f)(const scv_report *));

   // get unused action (returns SCV_UNSPECIFIED if none available)
   static scv_actions get_new_action_id();

   // control log file name
   static const char *get_log_file_name();
   static void set_log_file_name(const char *name);

   // control debug output for scv_report
   static int get_debug() { return _debug; }
   static void set_debug(int debug) { _debug = debug; }

   //
   // use reporting facility
   //

   // user can intercept with set_handler
   static void report(
     scv_severity severity, scv_msg_type msg_type,
     const char *msg,
     const char *file_name, int line_number
   );

   // always calls default handler
   static void default_handler(const scv_report&, const scv_actions&);

   static const scv_report *get_cached_report();
   static void clear_cached_report();

private:

   // set default configuration
   static void initialize();

   static int _debug;
};


const scv_actions SCV_DEFAULT_INFO_ACTIONS
       = SCV_LOG | SCV_DISPLAY;
const scv_actions SCV_DEFAULT_WARNING_ACTIONS
       = SCV_LOG | SCV_DISPLAY;
const scv_actions SCV_DEFAULT_ERROR_ACTIONS
       = SCV_LOG | SCV_DISPLAY | SCV_CACHE_REPORT | SCV_THROW;
const scv_actions SCV_DEFAULT_FATAL_ACTIONS
       = SCV_LOG | SCV_DISPLAY | SCV_CACHE_REPORT | SCV_THROW;


#endif // ! _SCV_USE_SC_REPORT


//
// Translation layer for _scv_message messages
//


class _scv_message_desc {
public:
  _scv_message_desc(
    string tag, string format, scv_severity severity, scv_actions actions
  ) : _tag(tag), _format(format), _severity(severity), _actions(actions) {}
  const char *get_tag() const { return _tag.c_str(); }
  const char *get_format() const { return _format.c_str(); }
  scv_severity get_severity() const { return _severity; }
  unsigned get_actions() const { return _actions; }
private:
  string _tag;
  string _format;
  scv_severity _severity;
  scv_actions _actions;
};


class _scv_message {
friend class scv_report_core;
public:

  enum severity_level { INFO, WARNING, ERROR, FATAL };

  enum response_level {
    NONE_SPECIFIED, ENABLE_MESSAGE, SUPPRESS_MESSAGE
  };

// Message types are actually pointers to descriptors
#define _SCV_DEFERR(code, number, string, severity, actions) \
  static _scv_message_desc *code##_base; \
  static _scv_message_desc **code;
#include "scv/scv_messages.h"
#undef _SCV_DEFERR

  // Used internally by the SystemC Verification Standard to report exceptions
  static void message(_scv_message_desc **desc_pp, ... );
  static scv_severity xlat_severity(severity_level severity);

private:
  static void setup();
};


#endif // ! _SCV_REPORT_H 
