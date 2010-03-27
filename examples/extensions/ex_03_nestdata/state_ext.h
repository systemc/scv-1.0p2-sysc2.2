// nbcode "inc" start
#ifndef STATE_EXT_H
#define STATE_EXT_H

#include "scv.h"
#include "state.h"
// nbcode "inc" end

// nbcode "enum" start
template<>
class scv_extensions<state_t::onehot_t> : public scv_enum_base<state_t::onehot_t> {
public:

  SCV_ENUM_CTOR(state_t::onehot_t) {
    SCV_ENUM(state_t::STATE_0);
    SCV_ENUM(state_t::STATE_1);
    SCV_ENUM(state_t::STATE_2);
    SCV_ENUM(state_t::STATE_3);
    SCV_ENUM(state_t::STATE_4);
    SCV_ENUM(state_t::STATE_5);
    SCV_ENUM(state_t::STATE_6);
  }
};
// nbcode "enum" end

// nbcode "state" start
template<>
class scv_extensions<state_t> : public scv_extensions_base<state_t> {
public:
  scv_extensions<state_t::onehot_t > state;
  scv_extensions<int      > delay;
  scv_extensions<unsigned > data;

  SCV_EXTENSIONS_CTOR(state_t) {
    //must be in order
    SCV_FIELD(state);
    SCV_FIELD(delay);
    SCV_FIELD(data);
  }
};
// nbcode "state" end
#endif //STATE_EXT_H
