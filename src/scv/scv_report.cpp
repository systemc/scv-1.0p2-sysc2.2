//  -*- C++ -*- <this line is for emacs to recognize it as C++ code>
/*****************************************************************************

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

  scv_report.cpp -- A trace/debug facility for the SystemC Verification
  Standard library

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

//
// This must be included before any system headers.
//
#include "scv.h"

#include <stdarg.h>
#include <string>
#include <map>


//
// used in implementation of scv_report
//


#define _SCV_DEBUG_CHECK(level) SCV_DEBUG_CHECK(scv_report_handler::get_debug(),(level))


template<typename KEY, typename VAL>
class xref {
  typedef map<KEY,VAL> map_t;
  typedef typename map_t::const_iterator const_iterator;
  typedef typename map_t::iterator iterator;
public:
  xref(VAL val) : _default(val) {}
  VAL get(const KEY key) const {
    const_iterator _iter = _map.find(key);
    return ( _iter == _map.end() ) ? _default : _iter->second;
  }
  VAL incr(KEY key) { // ++_map[key]
    iterator _iter = _map.find(key);
    if ( _iter == _map.end() ) { _map[key] = 1; return 1; }
    else return ++(_iter->second);
  }
  VAL set(KEY key, VAL val) {
    VAL prv = get(key);
    _map[key] = val;
    return prv;
  }
private:
  map_t _map;
  VAL _default;
};


template<typename VAL>
class rules {
public:
  rules(VAL val)
    : _map_sev(val), _map_msg(val), _map_com(val) {}
  unsigned get(scv_severity severity) const
    { return _map_sev.get(severity); }
  unsigned get(scv_msg_type msg_type) const
    { return _map_msg.get(msg_type); }
  unsigned get(scv_msg_type msg_type, scv_severity severity) const
    { return _map_com.get( _scv_make_unique_name(msg_type,severity) ); }
  unsigned incr(scv_severity severity)
    { return _map_sev.incr(severity); }
  unsigned incr(scv_msg_type msg_type)
    { return _map_msg.incr(msg_type); }
  unsigned incr(scv_msg_type msg_type, scv_severity severity)
    { return _map_com.incr( _scv_make_unique_name(msg_type,severity) ); }
  unsigned set(unsigned severity, VAL val)
    { return _map_sev.set(severity,val); }
  unsigned set(scv_msg_type msg_type, VAL val)
    { return _map_msg.set(msg_type,val); }
  unsigned set(scv_msg_type msg_type, scv_severity severity, VAL val)
    { return _map_com.set( _scv_make_unique_name(msg_type,severity), val ); }
private:
  xref<unsigned,VAL> _map_sev;
  xref<string,VAL> _map_msg;
  xref<string,VAL> _map_com;
};


class mask {
public:
  mask(scv_actions val) : _mask(val) {}
  scv_actions get() const { return _mask; }
  scv_actions set(scv_actions val) {
    scv_actions prv = _mask; _mask = val; return prv;
  }
private:
  scv_actions _mask;
};


class scv_report_core {
public:
  rules<scv_actions> actions;
  rules<int> limits;
  rules<int> counts;
  mask force;
  mask suppress;
  scv_report_core()
    : actions(SCV_UNSPECIFIED)
    , limits(-1)
    , counts(0)
    , force(0)
    , suppress(0)
    {}
  void initialize() {
    actions.set((unsigned)SCV_INFO,SCV_DEFAULT_INFO_ACTIONS);
    actions.set((unsigned)SCV_WARNING,SCV_DEFAULT_WARNING_ACTIONS);
    actions.set((unsigned)SCV_ERROR,SCV_DEFAULT_ERROR_ACTIONS);
    actions.set((unsigned)SCV_FATAL,SCV_DEFAULT_FATAL_ACTIONS);
  }
  static scv_report_core *get_core() {
    static scv_report_core *core_p = 0;
    if ( ! core_p ) {
      core_p = new scv_report_core;
      core_p->initialize();
      _scv_message::setup();
    }
    return core_p;
  }
};


#ifndef _SCV_USE_SC_REPORT


static string& severity_string(scv_severity severity)
{
  static string info = "SCV_INFO";
  static string warning = "SCV_WARNING";
  static string error = "SCV_ERROR";
  static string fatal = "SCV_FATAL";
  static string unknown = "???";
  switch ( severity ) {
    case SCV_INFO    : return info;
    case SCV_WARNING : return warning;
    case SCV_ERROR   : return error;
    case SCV_FATAL   : return fatal;
    default	     : return unknown;
  }
}


#if !( defined SYSTEMC_VERSION ) || ( SYSTEMC_VERSION < 20060204 )

static scv_report *_update_report_cache(scv_report *newp, bool replace)
{
  typedef map<sc_process_b*,scv_report*> map_t;
  static map_t _map;

  sc_process_b *key = sc_get_curr_process_handle();
  map_t::const_iterator _iter = _map.find(key);
  scv_report *curr = ( _iter == _map.end() ) ? 0 : _iter->second;

  if ( replace ) {
    if ( curr ) delete curr;
    _map[key] = curr = newp;
  }
  return curr;
}

#else  //SystemC 2.2

static scv_report *_update_report_cache(scv_report *newp, bool replace)
{
  typedef map<sc_process_b*,scv_report*> map_t;
  static map_t _map;

  sc_process_b* key = sc_core::sc_get_current_process_b();
  map_t::const_iterator _iter = _map.find(key);
  scv_report *curr = ( _iter == _map.end() ) ? 0 : _iter->second;

  if ( replace ) {
    if ( curr ) delete curr;
    _map[key] = curr = newp;
  }
  return curr;
}


#endif //!( defined SYSTEMC_VERSION ) || ( SYSTEMC_VERSION < 20060204 )


//
// Implementation of scv_report
//


void scv_interrupt_here(const scv_msg_type& id) {}
void scv_stop_here() {}


const char *scv_report::_kind = "scv_report";

scv_report::scv_report(
  scv_severity severity, scv_msg_type msg_type,
  const char *msg,
  const char *file_name, int line_number,
  sc_time time, const char *process_name
)
: _severity(severity), _msg_type(msg_type)
, _msg(msg)
, _file_name(file_name), _line_number(line_number)
, _time(time), _process_name(process_name)
{}

scv_report::scv_report(const scv_report& src)
: _severity(src._severity), _msg_type(src._msg_type)
, _msg(src._msg)
, _file_name(src._file_name), _line_number(src._line_number)
, _time(src._time), _process_name(src._process_name)
{}

void scv_report::print(ostream& os, int details, int indent) const
{
  scv_debug::indent(os,indent);
  os << "scv_report: severity: " << severity_string(_severity)
     << " msg_type: " << _msg_type
     << " time: " << _time << " process: " << _process_name << endl;
  if ( ! details ) return;
  scv_debug::indent(os,indent+2);
  os << "msg: " << _msg << endl;
  scv_debug::indent(os,indent+2);
  os << "file: " << _file_name << " line: " << _line_number << endl;
}

scv_report& scv_report::operator=(const scv_report& src)
{
  _severity = src._severity;
  _msg_type = src._msg_type;
  _msg = src._msg;
  _file_name = src._file_name;
  _line_number = src._line_number;
  _time = src._time;
  _process_name = src._process_name;

  return *this;
}

scv_report::operator const char *() const
{
  static char *buf = new char[1024];
  static int max = 1024;
  int len = 10 + 32 + 10 + _msg_type.size() + 6 + 32 + 9 + _process_name.size()
	  + 6 + _file_name.size() + 6 + 32 + 5 + _msg.size() +1;
  if ( len > max ) {
    max = len;
    delete [] buf;
    buf = new char[max];
  }
  sprintf(
    buf,
    "severity: %s msg_type: %s time: %s process: %s file: %s line: %d msg: %s",
    severity_string(_severity).c_str(), _msg_type.c_str(),
    _time.to_string().c_str(), _process_name.c_str(), _file_name.c_str(),
    _line_number, _msg.c_str()
  );
  return buf;
}


//
// Implementation of scv_report_handler
//


int scv_report_handler::_debug = -1;

static void (*_scv_report_handler)(const scv_report&, const scv_actions&)
  = &scv_report_handler::default_handler;

static scv_actions _scv_new_action_id = 0x0100;

static char *_scv_log_file_name = 0;

static ofstream *_scv_log_file_stream = 0;

typedef void (*cb_ptr)(const scv_report *);
static list<cb_ptr> *cb_list_p = NULL;


void scv_report_handler::set_handler(
  void (*handler)(const scv_report&, const scv_actions&)
)
{
  if ( handler ) _scv_report_handler = handler;
  else _scv_report_handler = &scv_report_handler::default_handler;
}

scv_actions scv_report_handler::set_actions(
  scv_severity severity, scv_actions actions
)
{
  scv_report_core *cp = scv_report_core::get_core();
  if ( _SCV_DEBUG_CHECK(1) ) {
    scv_actions old = cp->actions.get(severity);
    scv_out << "scv_report_handler::set_actions severity " << severity_string(severity)
            << " actions " << old << " --> " << actions << endl;
  }
  return cp->actions.set(severity,actions);
}

scv_actions scv_report_handler::set_actions(
  scv_msg_type msg_type, scv_actions actions
)
{
  scv_report_core *cp = scv_report_core::get_core();
  if ( _SCV_DEBUG_CHECK(1) ) {
    scv_actions old = cp->actions.get(msg_type);
    scv_out << "scv_report_handler::set_actions msg_type " << msg_type
            << " actions " << old << " --> " << actions << endl;
  }
  return cp->actions.set(msg_type,actions);
}

scv_actions scv_report_handler::set_actions(
  scv_msg_type msg_type, scv_severity severity,
  scv_actions actions
)
{
  scv_report_core *cp = scv_report_core::get_core();
  if ( _SCV_DEBUG_CHECK(1) ) {
    scv_actions old = cp->actions.get(msg_type,severity);
    scv_out << "scv_report_handler::set_actions msg_type " << msg_type
            << " severity " << severity_string(severity)
            << " actions " << old << " --> " << actions << endl;
  }
  return cp->actions.set(msg_type,severity,actions);
}

int scv_report_handler::stop_after(
  scv_severity severity, int limit
)
{
  scv_report_core *cp = scv_report_core::get_core();
  if ( _SCV_DEBUG_CHECK(1) ) {
    int old = cp->limits.get(severity);
    scv_out << "scv_report_handler::stop_after severity " << severity_string(severity)
            << " limit " << old << " --> " << limit << endl;
  }
  return cp->limits.set(severity,limit);
}

int scv_report_handler::stop_after(
  scv_msg_type msg_type, int limit
)
{
  scv_report_core *cp = scv_report_core::get_core();
  if ( _SCV_DEBUG_CHECK(1) ) {
    int old = cp->limits.get(msg_type);
    scv_out << "scv_report_handler::stop_after msg_type " << msg_type
            << " limit " << old << " --> " << limit << endl;
  }
  return cp->limits.set(msg_type,limit);
}

int scv_report_handler::stop_after(
  scv_msg_type msg_type, scv_severity severity,
  int limit
)
{
  scv_report_core *cp = scv_report_core::get_core();
  if ( _SCV_DEBUG_CHECK(1) ) {
    int old = cp->actions.get(msg_type,severity);
    scv_out << "scv_report_handler::stop_after msg_type " << msg_type
            << " severity " << severity_string(severity)
            << " limit " << old << " --> " << limit << endl;
  }
  return cp->limits.set(msg_type,severity,limit);
}

void scv_report_handler::initialize()
{
  scv_report_core *cp = scv_report_core::get_core();
  if ( _SCV_DEBUG_CHECK(1) ) {
    scv_out << "scv_report_handler::initialize" << endl;
  }
  cp->initialize();
}

scv_actions scv_report_handler::suppress(scv_actions actions)
{
  scv_report_core *cp = scv_report_core::get_core();
  if ( _SCV_DEBUG_CHECK(1) ) {
    scv_actions old = cp->suppress.get();
    scv_out << "scv_report_handler::suppress actions " << old << " --> " << actions << endl;
  }
  return cp->suppress.set(actions);
}

scv_actions scv_report_handler::force(scv_actions actions)
{
  scv_report_core *cp = scv_report_core::get_core();
  if ( _SCV_DEBUG_CHECK(1) ) {
    scv_actions old = cp->force.get();
    scv_out << "scv_report_handler::force actions " << old << " --> " << actions << endl;
  }
  return cp->force.set(actions);
}

void scv_report_handler::register_cb(cb_ptr f)
{
  if ( ! cb_list_p ) cb_list_p = new list<cb_ptr>();
  cb_list_p->push_front(f);
}


scv_actions scv_report_handler::get_new_action_id()
{
  // _scv_new_action_id initially set to new action
  // after predefined ones; once we're out of bits
  // it'll roll over to 0, and stay 0.
  scv_actions new_action_id = _scv_new_action_id;
  _scv_new_action_id <<= 1;
  return new_action_id;
}

const char *scv_report_handler::get_log_file_name()
{ return _scv_log_file_name; }

void scv_report_handler::set_log_file_name(const char *name)
{
  assert(name);
  if ( _scv_log_file_stream ) return;
  if ( _scv_log_file_name ) delete [] _scv_log_file_name;
  _scv_log_file_name = new char[ strlen(name) +1 ];
  strcpy(_scv_log_file_name,name);
}


void scv_report_handler::default_handler(
  const scv_report& report, const scv_actions& actions
)
{
  scv_severity severity = report.get_severity();
  scv_msg_type msg_type = report.get_msg_type();
  const char *msg = report.get_msg();
  sc_time time = report.get_time();
  const char *process = report.get_process_name();
  const char *file_name = report.get_file_name();
  int line_number = report.get_line_number();

  scv_report_core *cp = scv_report_core::get_core();

  int sev_count = cp->counts.incr(severity);
  int msg_count = cp->counts.incr(msg_type);
  int com_count = cp->counts.incr(msg_type,severity);

  bool stop_flag = false;
  int limit = cp->limits.get(msg_type,severity);
  if ( limit == -1 ) {
    limit = cp->limits.get(msg_type);
    if ( limit == -1 ) {
      limit = cp->limits.get(severity);
      if ( limit == -1 ) {
	if ( severity == SCV_FATAL ) { limit = 1; stop_flag = true; }
      }
      else if ( limit == 0 ) ;
      else if ( sev_count >= limit ) stop_flag = true;
    }
    else if ( limit == 0 ) ;
    else if ( msg_count >= limit ) stop_flag = true;
  }
  else if ( limit == 0 ) ;
  else if ( com_count >= limit ) stop_flag = true;

  string label = severity_string(severity);

  if ( actions & SCV_LOG ) {
    if ( _scv_log_file_name && ! _scv_log_file_stream ) {
      _scv_log_file_stream = new ofstream(_scv_log_file_name);
      if ( ! *_scv_log_file_stream ) {
	char image[1024];
	sprintf(image,"Cannot open log file \"%s\"",_scv_log_file_name);
	delete [] _scv_log_file_name;
	_scv_log_file_name = 0;
	SCV_REPORT_ERROR("LOG_FILE_ERROR",image);
	delete _scv_log_file_stream;
	_scv_log_file_stream = 0;
      }
    }
    if ( _scv_log_file_stream ) {
      *_scv_log_file_stream << endl
        << "*** " << label << ": " << msg_type
        << " at time " << time << " in process " << process << endl
        << "    " << msg << endl;
    }
  }

  if ( actions & SCV_DISPLAY ) {
    scv_out << endl
            << "*** " << label << ": " << msg_type
            << " at time " << time << " in process " << process << endl
            << "    " << msg << endl;
  }

  if ( cb_list_p ) {
    scv_report report(severity,msg_type,msg,file_name,line_number,time,process);
    list<cb_ptr>::iterator i;
    for ( i = cb_list_p->begin(); i != cb_list_p->end(); i++ ) {
      (**i)(&report);
    }
  }

  if ( actions & SCV_ABORT ) {
    scv_out << endl
            << "*** " << severity_string(SCV_FATAL) << ": SCV_ABORT" << endl
            << "    Simulation is now ending." << endl;
    abort();
  }

  if ( stop_flag ) {
    scv_out << endl
            << "*** " << severity_string(SCV_FATAL) << ": " << "SCV_MESSAGE_LIMIT"
            << " at time " << time << " in process " << process << endl
            << "    You have reached the " << label << " message limit of "
            << limit << "." << endl
            << "    Simulation is now ending." << endl;
    sc_stop();
  }

  if ( actions & SCV_STOP ) {
    scv_out << endl
            << "*** " << severity_string(SCV_FATAL) << ": SCV_STOP" << endl
            << "    Simulation is now ending." << endl;
    sc_stop();
  }

  if ( actions & SCV_CACHE_REPORT ) {
    _update_report_cache( new scv_report(report), true );
  }

  if ( actions & SCV_THROW ) throw scv_report(report);

  if ( actions & SCV_INTERRUPT ) scv_interrupt_here(msg_type);
}

void scv_report_handler::report(
  scv_severity severity, scv_msg_type msg_type,
  const char *msg,
  const char *file_name, int line_number
)
{
  scv_stop_here();

  scv_report_core *cp = scv_report_core::get_core();

  scv_actions actions = cp->actions.get(msg_type,severity);
  if ( actions == SCV_UNSPECIFIED ) actions = cp->actions.get(msg_type);
  if ( actions == SCV_UNSPECIFIED ) actions = cp->actions.get(severity);

  scv_actions hold;
  hold = cp->suppress.get();
  actions &= ~hold;
  hold = cp->force.get();
  actions |= hold;

  sc_time time = sc_time_stamp();
#if !( defined SYSTEMC_VERSION ) || ( SYSTEMC_VERSION < 20060204 )
  const char *process = scv_get_process_name( sc_get_curr_process_handle() );
#else
  const char *process = scv_get_process_name( sc_get_current_process_handle() );
#endif

  scv_report report(
    severity, msg_type, msg,
    file_name, line_number, time, process
  );

  _scv_report_handler(report,actions);
}

const scv_report *scv_report_handler::get_cached_report()
{ return _update_report_cache(0,false); }

void scv_report_handler::clear_cached_report()
{ _update_report_cache(0,true); }


#endif // ! _SCV_USE_SC_REPORT


//
// Implementation of _scv_message
//


#define _SCV_DEFERR(code, number, string, severity, stack_action) \
  _scv_message_desc *_scv_message::code##_base = 0; \
  _scv_message_desc **_scv_message::code = &_scv_message::code##_base;
#include "scv/scv_messages.h"
#undef _SCV_DEFERR


void _scv_message::message(_scv_message_desc **desc_pp, ...)
{
  // make sure desc is defined
  scv_report_core::get_core();

  _scv_message_desc *desc_p = *desc_pp;

  const char *tag = desc_p->get_tag();
  const char *format = desc_p->get_format();
  scv_severity severity = desc_p->get_severity();
  scv_actions actions = desc_p->get_actions();

  scv_actions hold = scv_report_handler::force(0);
  scv_report_handler::force(hold|actions);

  static char formattedMessageString[20000];
  va_list ap;
  va_start(ap,desc_pp);
  vsprintf(formattedMessageString,format,ap);
  va_end(ap);

  scv_report_handler::report(severity,tag,formattedMessageString,"unknown",0);

  scv_report_handler::force(hold);
}

void _scv_message::setup()
{
  static bool first_time = true;
  if ( first_time ) first_time = false;
  else return;
#define _SCV_DEFERR(code, number, string, severity, stack_action) \
  code##_base = new _scv_message_desc(#code,string,xlat_severity(severity),SCV_DO_NOTHING);
#include "scv/scv_messages.h"
#undef _SCV_DEFERR
  scv_report_handler::set_actions(SCV_ERROR,SCV_LOG|SCV_DISPLAY|SCV_CACHE_REPORT);
  scv_report_handler::set_actions(SCV_FATAL,SCV_LOG|SCV_DISPLAY|SCV_CACHE_REPORT);
}

scv_severity _scv_message::xlat_severity(severity_level severity)
{
  switch ( severity ) {
    case INFO    : return SCV_INFO;
    case WARNING : return SCV_WARNING;
    case ERROR   : return SCV_ERROR;
    default	 : return SCV_FATAL;
  }
}
