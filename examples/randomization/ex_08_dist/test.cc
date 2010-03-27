#include "data_ext.h"

#ifdef _MSC_VER
#include <iomanip>
#else
#include <iomanip.h>
#endif

void stateOut(scv_smart_ptr<data_t> data_p, int count[], onehot_t state) {
  scv_out << setw(0) << data_p->state.get_enum_string(state) << ": "
          << setw(4) << count[state] << endl;
}

// nbcode "decl" start
int sc_main(int argc, char** argv) {
  scv_smart_ptr<data_t> data_p("data");
  const int loopCount = 1000;
  int count[STATE_6+1];
  int total = 0;
  // nbcode "decl" end

  // nbcode "def" start
  //create a distribution for generating the state data
  //highest probabilty for states 1-4, zero chance for 3 and
  //lower probability for 0, 5, and 6.
  scv_bag<onehot_t> state_dist("state_dist");
  state_dist.add(STATE_0, 10);
  state_dist.add(STATE_1, 25);
  state_dist.add(STATE_2, 25);
  state_dist.add(STATE_4, 25);
  state_dist.add(STATE_5, 10);
  state_dist.add(STATE_6, 5);

  //set the distribution for the state variable in data_p
  data_p->state.set_mode(state_dist);
  // nbcode "def" end

  // nbcode "gen" start
  //initialize our counting array
  for (int i=0; i<STATE_6+1; i++) count[i] = 0;

  //randomize data loopCount times and track the results
  for(int i=0; i<loopCount; ++i) {
    data_p->next();
    count[data_p->state]++;
    total++;
  }
  // nbcode "gen" end

  // nbcode "out" start
  //print number of occurrences of each state
  stateOut(data_p, count, STATE_0);
  stateOut(data_p, count, STATE_1);
  stateOut(data_p, count, STATE_2);
  stateOut(data_p, count, STATE_3);
  stateOut(data_p, count, STATE_4);
  stateOut(data_p, count, STATE_5);
  stateOut(data_p, count, STATE_6);
  scv_out << "         ====" << endl;
  scv_out << "  Total: " << setw(4) << total << endl << endl;
  // nbcode "out" end

  return 0;
}
