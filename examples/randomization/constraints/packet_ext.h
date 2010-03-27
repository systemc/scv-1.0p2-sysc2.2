//  -*- C++ -*- <this line is for emacs to recognize it as C++ code>
/*****************************************************************************
 packet_ext.h --
  
 File created using tb_wizard from the "packet" data type defined in packet.h 

 *****************************************************************************/

#ifndef PKT_EXT_H
#define PKT_EXT_H

#include "packet.h"

SCV_ENUM_EXTENSIONS(packet_types_t) {
 public:
  SCV_ENUM_CTOR(packet_types_t) {
    SCV_ENUM(UNICAST);
    SCV_ENUM(MULTICAST);
  };
};

SCV_EXTENSIONS(packet) {
 public:
    scv_extensions< packet_types_t > ptype;
    scv_extensions< sc_uint<8> > source;
    scv_extensions< sc_uint<8> > destination;

  SCV_EXTENSIONS_CTOR(packet) {
    SCV_FIELD(ptype);
    SCV_FIELD(source);
    SCV_FIELD(destination);
  }

};

#endif // PKT_EXT_H


