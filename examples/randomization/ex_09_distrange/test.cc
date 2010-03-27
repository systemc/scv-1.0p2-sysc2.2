#include "data_ext.h"

#ifdef _MSC_VER
#include <iomanip>
#else
#include <iomanip.h>
#endif

// nbcode "decl" start
int sc_main(int argc, char** argv) {
  scv_smart_ptr<data_t> data_p("data");
  scv_random::set_global_seed(666);
  // nbcode "decl" end

  // nbcode "track_decl" start
  #define FIELD_PAIR pair<sc_uint<8>, sc_uint<8> >
  class rangeDef {
  public:
    FIELD_PAIR range;
    int percentage, count;
    bool InRange(sc_uint<8> val)
    {
      return (val >= range.first && val <= range.second);
    }
    rangeDef() {count = 0;}
  };
  const int numRanges = 4;
  rangeDef ranges[numRanges];
  int total = 0;
  const int loopCount = 1000;
  // nbcode "track_decl" end

  // nbcode "def" start
  //create a non-linear approximation for field using ranges,
  //initialize tracking count
  ranges[0].range = FIELD_PAIR(0x00, 0x02);  // 0-2
  ranges[1].range = FIELD_PAIR(0x03, 0x06);  // 3-6
  ranges[2].range = FIELD_PAIR(0x07, 0x0f);  // 7-15
  ranges[3].range = FIELD_PAIR(0x10, 0xff);  // 16-255

  ranges[0].percentage = 60;
  ranges[1].percentage = 20;
  ranges[2].percentage = 10;
  ranges[3].percentage = 10;

  //declare and fill our bag with the distribution information
  scv_bag< FIELD_PAIR > field_dist;
  for (int i=0; i<numRanges; i++) {
    field_dist.add(ranges[i].range, ranges[i].percentage);
  }

  //set the distribution for the field variable in data_p
  data_p->field.set_mode(field_dist);
  // nbcode "def" end

  // nbcode "gen" start
  //randomize data loopcount times and print the results
  for(int i=0; i<loopCount; ++i) {
    data_p->next();
    for (int j=0; j<numRanges; j++) {
      if (ranges[j].InRange(data_p->field.read())) {
        ranges[j].count++;
        total++;
        break;
      }
    }
  }
  // nbcode "gen" end

  // nbcode "print" start
  //print distribution
  for (int i=0; i<numRanges; i++) {
    scv_out << "Range " << setw(2) << i << ": "
            << setw(3) << ranges[i].range.first << "-"
            << setw(3) << ranges[i].range.second << "  "
            << setw(4) << ranges[i].count << endl;
  }
  scv_out << "                   ====" << endl;
  scv_out << "            Total: " << setw(4) << total << endl << endl;
  // nbcode "print" end

  return 0;
}
