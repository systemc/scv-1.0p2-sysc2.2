#include "constraint.h"

#ifdef _MSC_VER 
#include <iomanip>
#else
#include <iomanip.h>
#endif 

// nbcode "head" start
SC_MODULE(test) {
  sc_signal<unsigned> addr;
  my_constraint cnstr;
  // nbcode "head" end

  // nbcode "ctor" start
  SC_CTOR(test) : cnstr("cnstr") {
    cnstr.set_sig(&addr);
    SC_THREAD(run);
  }
  // nbcode "ctor" end

  // nbcode "method" start
  void run() {
    unsigned i;
    for(i=10; i<100; i+=20) {
      addr=i;
      scv_out << "addr = " << setw(2) << addr << ", Setting to "
              << setw(2) << i << endl;
      wait(0, SC_NS);
      cnstr.next();
      scv_out << "addr = " << setw(2) << addr << ", rval = "
              << setw(2) << *cnstr.rval << "\n" << endl;
      wait(10, SC_NS);
    }
    sc_stop();
  }
  // nbcode "method" end
};
