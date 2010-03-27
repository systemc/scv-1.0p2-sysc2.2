#include "data_ext.h"

int sc_main(int argc, char** argv) {
  scv_smart_ptr<data_t> data_p("data");

  //set the global seed to that results will be consistent
  scv_random::set_global_seed(100);

        // nbcode "disable" start
  //set the values of the array element
  for(unsigned i=0; i<5; ++i) data_p->payload[i] = i*i;

  //turn off randomization for the even array elements
  for(unsigned i=0; i<5; i+=2) 
    data_p->payload[i].disable_randomization();
  // nbcode "disable" end

  //randomize composit
  data_p->next();

  scv_out << "Random value for " << data_p->get_name() << ":" << endl;
  data_p->print(scv_out);

  return 0;
}


