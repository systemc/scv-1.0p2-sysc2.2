//  -*- C++ -*- <this line is for emacs to recognize it as C++ code>
/*****************************************************************************
 packet.cpp -- 
  
 Implementation for packet class. dump method shows the use of static extensions
 in the implementation of packet methods itself.
  
 *****************************************************************************/

#include "packet_ext.h"

// --------------------------------------------------------------
// constructors & copy assignment
packet::packet() {
  ptype = UNICAST;
};

packet::packet(const packet & src) : ptype(src.ptype), source(src.source), destination(src.destination) { };

const packet & packet::operator=(const packet & src) {
  ptype = src.ptype;
  source  = src.source;
  destination  = src.destination;
  return *this;
}; // packet & operator=

// --------------------------------------------------------------
//
// We could use print() (from the scv_extensions utility interface)
// in place of this function.  However, the interest in this function
// is not so much what it does, but to demonstrate how to access
// functions within classes from higher levels in the program.
//
void packet::dump(void) const {
  const scv_extensions<packet> p = scv_get_const_extensions(*this);
  cout << "  " << p.ptype.get_enum_string(p.ptype);

  cout << " " << source;
  cout << " " << destination << endl;
}
   


