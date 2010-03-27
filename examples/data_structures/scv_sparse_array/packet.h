#include "scv.h"

#ifdef _MSC_VER 
#include <iomanip>
#else
#include <iomanip.h>
#endif 

#ifndef PACKET_H
#define PACKET_H

// Define a packet with a variable size payload

// nbcode "fields" start
class packetT {
  public:
    packetT () {}
    virtual ~packetT() {}

    // Packet's data
    sc_uint<16> src;
    sc_uint<16> dest;
    sc_uint<16> length; // Number of items in the payload
    sc_uint<16> payload[1024];
    // nbcode "fields" end

    // nbcode "assign" start
    // Define an equal operator
    packetT& operator=(const packetT& rhs) {
      src=rhs.src; dest=rhs.dest; length=rhs.length;
      for(unsigned int i=0; (i<length) && (i<1024); i++)
        payload[i]=rhs.payload[i];
      return *this;
    }
    // nbcode "assign" end

    // nbcode "compare" start
    // Define a comparison operator
    friend bool operator==(const packetT& a, const packetT& b) {
      if (a.src != b.src) {return false;}
      if (a.dest != b.dest) {return false;}
      if (a.length != b.length) {return false;}
      for(unsigned int i=0; (i<a.length) && (i<1024); i++)
        if (a.payload[i] != b.payload[i]) {return false;}
      return true;
    }
    // Define a not-equal operator (some compilers do not
    // automatically create this from operator=)
    friend bool operator!=(const packetT& a, const packetT& b) {
      if (a.src != b.src) {return true;}
      if (a.dest != b.dest) {return true;}
      if (a.length != b.length) {return true;}
      for(unsigned int i=0; (i<a.length) && (i<1024); i++)
        if (a.payload[i] != b.payload[i]) {return true;}
      return false;
    }
    // nbcode "compare" end

    // nbcode "out" start
    // Define ostream method to print data
    friend ostream& operator<< (ostream& os, const packetT& p) {
      os << "  src: "     << setw(5) << p.src
         << "  dest: "    << setw(5) << p.dest
         << "  length: "  << setw(4) << p.length 
         << "  payload: " << setw(5) << p.payload[0]
         << " .. "        << setw(5) << p.payload[p.length-1];
      return os;
    }
};
// nbcode "out" end

// nbcode "ext" start
// Extensions to packetT
template<>
class scv_extensions<packetT> : public scv_extensions_base<packetT> {
public:
  scv_extensions< sc_uint<16>       > src;
  scv_extensions< sc_uint<16>       > dest;
  scv_extensions< sc_uint<16>       > length;
  scv_extensions< sc_uint<16>[1024] > payload;

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
