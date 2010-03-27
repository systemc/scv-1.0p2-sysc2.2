#include "scv.h"

// nbcode "decl" start
class my_constraint : public scv_constraint_base {
  protected:
    sc_signal<unsigned> *sig_;
    scv_smart_ptr<unsigned> val;

  public:
    scv_smart_ptr<unsigned> rval;
    // nbcode "decl" end

    // nbcode "ctor" start
    SCV_CONSTRAINT_CTOR(my_constraint) {
      val->disable_randomization();
      *val = 5;
      sig_ = NULL;
      SCV_CONSTRAINT( rval() < (val() + 5) );
      SCV_CONSTRAINT( rval() > (val() - 5) );
      SCV_CONSTRAINT( rval() != val() );
    }
    // nbcode "ctor" end

    // nbcode "methods" start
  public:
    void set_sig (sc_signal<unsigned>* sigp) { sig_ = sigp; }
    virtual void next() {
      if(sig_ != NULL) {
        *val = sig_->read();
      }
      scv_constraint_base::next();
    }
    // nbcode "methods" end
};
