#include "scv.h"

#ifdef _MSC_VER
#include <iomanip>
#else
#include <iomanip.h>
#endif

// nbcode "def" start
//create a constraint class
struct addr_constraint : public scv_constraint_base {
  //create the objects that will be constrained
  scv_smart_ptr<int> row;
  scv_smart_ptr<int> col;

  SCV_CONSTRAINT_CTOR(addr_constraint) {
    //constraint row to be between 10 and 50 exclusive or 200 and 250
    //inclusive
    SCV_CONSTRAINT ( (row() > 10 && row() < 50)  || 
                    (row() >= 200 && row() <= 250) );

    //constraint col to be less than row+20 and greater than row-5
    //NOTE: if randomization is disabled on row, then row could be
    //any value. If row does not meet constraints an error
    //is generated.
    SCV_CONSTRAINT ( col() > ( row() - 5) );
    SCV_CONSTRAINT ( col() < ( row() + 20) );
  }
};
// nbcode "def" end

int sc_main (int argc, char** argv) {
  scv_random::set_global_seed(1023);

  // nbcode "decl" start
  //instantiate a constrained object
  addr_constraint addr("addr");
  // nbcode "decl" end

  //if you disable the constraint on row, col is still constrained
  //with respect to row. Uncommenting the following lines will
  //produce constraint errors because row does not satisfy the
  //constraints.
  //addr.row->disable_randomization();
  //*(addr.row) = 1000;

  // nbcode "print" start
  //randomize the object five times and print the values
  for(int i=0; i<5; ++i) {
    addr.next();
    scv_out << "Row: " << setw(3) << *(addr.row)
            << "; Col: " << setw(3) << *(addr.col) << endl;
  }
  scv_out << endl;
  // nbcode "print" end

  return 0;
}

