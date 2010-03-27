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

  _scv_data_structure.h -- 
  The base class of any data structure, specifying the interface
  common to them.

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

#ifndef SCV_DATA_STRUCTURE_H
#define SCV_DATA_STRUCTURE_H

#include "scv/scv_config.h"

#include <string>

#include "scv/scv_object_if.h"
#include "scv/scv_util.h"
#include "scv/scv_debug.h"

template<class T>
struct _scv_CstructMethods {
  _scv_CstructMethods() {
#if !defined(_USE_PADDING_ON_STRUCTS)
    memset(this,0,sizeof(T));
#else
    memset(this+4,0,sizeof(T)-4);
#endif
  }
  friend bool operator==(const _scv_CstructMethods<T>& a,
                         const _scv_CstructMethods<T>& b) {
#if !defined(_USE_PADDING_ON_STRUCTS)
    return 0==memcmp(&a,&b,sizeof(T));
#else
    return 0==memcmp(&a+4,&b+4,sizeof(T)-4);
#endif
  }
  friend bool operator<(const _scv_CstructMethods<T>& a,
                         const _scv_CstructMethods<T>& b) {
#if !defined(_USE_PADDING_ON_STRUCTS)
    return memcmp(&a,&b,sizeof(T))<0;
#else
    return memcmp(&a+4,&b+4,sizeof(T)-4)<0;
#endif
  }
  friend ostream& operator<<(ostream& os, const _scv_CstructMethods<T>&) {
    os << "< C-struct >";
    return os;
  }
  friend bool operator!=(const _scv_CstructMethods<T>& a,
                         const _scv_CstructMethods<T>& b) {
    return !(a==b);
  }
  friend bool operator>(const _scv_CstructMethods<T>& a,
                        const _scv_CstructMethods<T>& b) {
    return b<a;
  }
  friend bool operator<=(const _scv_CstructMethods<T>& a,
                        const _scv_CstructMethods<T>& b) {
    return a<b || a==b;
  }
  friend bool operator>=(const _scv_CstructMethods<T>& a,
                        const _scv_CstructMethods<T>& b) {
    return a>b || a==b;
  }
};

class _scv_data_structure : public scv_object_if {
public:

  //
  // virtual destructor
  //
  virtual ~_scv_data_structure() {};

  //
  // return the instance name of the data structure 
  //
  const char *get_name() const { return _name.c_str(); }

  virtual const char *kind() const { return _kind; }

  // 
  // print current values on output stream or on current screen
  //
  virtual void print(ostream& o, int details, int indent) const {};

  virtual void show(int details=0, int indent=0) const {
      print(scv_out, details, indent);
  }

  const char *nameP() const {  return _name.c_str(); }

  static int get_debug() {return _debug;} 

  static void set_debug(int debug)  {
    scv_debug::set_facility_level(scv_debug::DATA_STRUCTURES, debug);
    _debug = debug;
  }

//protected:
  //
  // constructor (all data structures have optional name)
  //
  _scv_data_structure(const char *name = "<anonymous>") : _name(name) {};
  string _name;
  static int _debug;
  static const char *_kind;

  static void set_class_debug(int debug) { _debug = debug; }
};

#endif // SCV_DATA_STRUCTURE_H
