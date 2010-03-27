#include "data_ext.h"

int sc_main(int argc, char** argv) {
  scv_smart_ptr<data_t> data_p("data");

  //set the values of the fields. Note: a scv_smart_ptr
  //works like a normal pointer object for accessing the
  //object.
  data_p->field_1 = 10;
  data_p->field_2 = 0xff;
  for(unsigned i=0; i<5; ++i) data_p->payload[i] = i*i;
  data_p->str = "my data string";

  scv_out << "Printing data in object " << data_p->get_name()
       << endl;
  data_p->print(); //print the object
  
  return 0;
}
