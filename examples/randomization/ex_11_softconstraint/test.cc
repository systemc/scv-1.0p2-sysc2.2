#include "scv.h"

// nbcode "def" start
//create a constraint class
struct addr_constraint : public scv_constraint_base {
  //create the objects that will be constrained
  scv_smart_ptr<int> row;
  scv_smart_ptr<int> col;

  SCV_CONSTRAINT_CTOR(addr_constraint) {
    string tmp = string(get_name()) + ".row";
    row->set_name(tmp.c_str());
    tmp = string(get_name()) + ".col";
    col->set_name(tmp.c_str());

    //soft constraint on row to be between 10 and 50 exclusive or
    //between 200 and 250 inclusive
    SCV_SOFT_CONSTRAINT ( (row() >   10 && row() <   50)  || 
                          (row() >= 200 && row() <= 250) );

    //hard constraint on row to be between the min and max
    //values in the soft constraint, eg, between 10 and 250
    SCV_CONSTRAINT ( (row() > 10) && (row() <= 250) );

    //hard constraint on col betwen row-5 and row+20
    SCV_CONSTRAINT ( col() > ( row() - 5) );
    SCV_CONSTRAINT ( col() < ( row() + 20) );
  }
};
// nbcode "def" end

int sc_main (int argc, char** argv) {
  scv_random::set_global_seed(0xCCCC);

  // nbcode "decl" start
  //instantiate a constrained object
  addr_constraint addr("addr");

  //disable randomization on col
  addr.col->disable_randomization();
  // nbcode "decl" end

  // nbcode "print" start
  //set value on col, and randomize the object 5 times
  int i, j;
  for(i=25, j=0; i<250; i+=50, ++j) {
    *(addr.col) = i;
    addr.next();
    scv_out << addr.row->get_name() << " = " << *(addr.row) << "\n"
            << addr.col->get_name() << " = " << *(addr.col) << "\n" << endl;
  }
  scv_out << endl;
  // nbcode "print" end

  return 0;
}
