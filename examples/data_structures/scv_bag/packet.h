#include "scv.h"

#ifdef _MSC_VER 
#include <iomanip>
#else
#include <iomanip.h>
#endif 

#ifndef PACKET_H
#define PACKET_H

//Create an object type that will be thrown in the bag. In this case,
//we will use the same basic type that we use for the smart queue example 

// nbcode "fields" start
//The bag will be defined as
//scv_bag<packetT>
class packetT {
  public:
    packetT() {}
    virtual ~packetT() {}

    //the data for the element
    sc_uint<16> src;
    sc_uint<16> dest;
    sc_uint<16> length;
    sc_uint<16> payload[1024];
    // nbcode "fields" end

    // nbcode "assign" start
    //define an equal operator. For this case it is not needed, but
    //in general it is a good idea to create equal operators for
    //data types that will be stored in data structures
    packetT& operator=(const packetT& rhs) {
      src=rhs.src; dest=rhs.dest; length=rhs.length;
      for(unsigned int i=0; (i<length) && (i<1024); i++)
        payload[i]=rhs.payload[i];
      return *this;
    }
    // nbcode "assign" end

    // nbcode "out" start
    //define an ostream method for printing the data
    friend ostream& operator<< (ostream& os, const packetT& p) {
      os << "   src: "    << setw(2) << p.src
         << "  dest: "    << setw(5) << p.dest
         << "  length: "  << setw(4) << p.length 
         << "  payload: " << setw(5) << p.payload[0]
         << " .. "        << setw(5) << p.payload[p.length-1];
      return os;
    }
};
// nbcode "out" end

// nbcode "ext" start
//add extension info here. Use tb_wizard_ext to auto generate
//SCV_EXTENSIONS(packetT);
template<>
class scv_extensions<packetT> : public scv_extensions_base<packetT> {
public:
  scv_extensions<sc_uint<16> > src;
  scv_extensions<sc_uint<16> > dest;
  scv_extensions<sc_uint<16> > length;
  scv_extensions<sc_uint<16> [1024]> payload;

  SCV_EXTENSIONS_CTOR(packetT) {
    //must be in order
    SCV_FIELD(src);
    SCV_FIELD(dest);
    SCV_FIELD(length);
    SCV_FIELD(payload);
  }
};
// nbcode "ext" end

#endif //PACKET_H
