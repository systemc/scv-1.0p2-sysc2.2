#ifndef DATA_EXT_H
#define DATA_EXT_H

#include "scv.h"
#include "data.h"

template<>
class scv_extensions<onehot_t> : public scv_enum_base<onehot_t> {
public:

  SCV_ENUM_CTOR(onehot_t) {
    SCV_ENUM(STATE_0);
    SCV_ENUM(STATE_1);
    SCV_ENUM(STATE_2);
    SCV_ENUM(STATE_3);
    SCV_ENUM(STATE_4);
    SCV_ENUM(STATE_5);
    SCV_ENUM(STATE_6);
  }
};

template<>
class scv_extensions<data_t> : public scv_extensions_base<data_t> {
public:
  scv_extensions<sc_uint<8> > field;
  scv_extensions<unsigned   [5]> payload;
  scv_extensions<onehot_t   > state;

  SCV_EXTENSIONS_CTOR(data_t) {
    //must be in order
    SCV_FIELD(field);
    SCV_FIELD(payload);
    SCV_FIELD(state);
  }
};
#endif //DATA_EXT_H
