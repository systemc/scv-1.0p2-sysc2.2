#ifndef DATA_EXT_H
#define DATA_EXT_H

#include "scv.h"
#include "data.h"


//declarations below this point are due to the --EXTEND_ALL option

template<>
class scv_extensions<data_t> : public scv_extensions_base<data_t> {
public:
  scv_extensions<int         > field_1;
  scv_extensions<sc_uint<8>  > field_2;
  scv_extensions<unsigned    [5]> payload;
  scv_extensions<string      > str;

  SCV_EXTENSIONS_CTOR(data_t) {
    //must be in order
    SCV_FIELD(field_1);
    SCV_FIELD(field_2);
    SCV_FIELD(payload);
    SCV_FIELD(str);
  }
};
#endif //DATA_EXT_H
