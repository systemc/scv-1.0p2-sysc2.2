//  -*- C++ -*- <this line is for emacs to recognize it as C++ code>
/*****************************************************************************
 packet.h --
  
 Define the composite type "packet" used in the Transaction level testbench.

 *****************************************************************************/

#ifndef PKT_H
#define PKT_H

#include "scv.h"

enum packet_types_t { UNICAST, MULTICAST };

class packet {
public:
  packet_types_t  ptype;
  sc_uint<8>      source;
  sc_uint<8>      destination;

public:
  packet(); 
  packet(const packet & src); 
  const packet & operator=(const packet & src);
  void dump(void) const;
}; // class packet ..

#endif


