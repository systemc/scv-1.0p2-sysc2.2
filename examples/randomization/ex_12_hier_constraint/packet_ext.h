#ifndef PACKET_EXT_H
#define PACKET_EXT_H

#include "scv.h"
#include "packet.h"

template<>
class scv_extensions<packet_t> : public scv_extensions_base<packet_t> {
public:
  scv_extensions<sc_uint<32> > src_addr;
  scv_extensions<sc_uint<32> > dest_addr;
  scv_extensions<sc_uint<16> > msg_length;
  scv_extensions<char        [1024]> msg;

  SCV_EXTENSIONS_CTOR(packet_t) {
    //must be in order
    SCV_FIELD(src_addr);
    SCV_FIELD(dest_addr);
    SCV_FIELD(msg_length);
    SCV_FIELD(msg);
  }
};
#endif //PACKET_EXT_H
