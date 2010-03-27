#include "state_ext.h"

int sc_main(int argc, char** argv) {
  scv_smart_ptr<state_t> st_p("state_data");

  //set the values of the fields. Note: a scv_smart_ptr
  //works like a normal pointer object for accessing the
  //object.
  st_p->state = STATE_3;
  st_p->delay = 2;
  st_p->data  = 0xaa;

  scv_out << "Printing data in object " << st_p->get_name()
          << endl;
  st_p->print(); //print the object

  return 0;
}
