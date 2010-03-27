#include "test.cc"

SC_MODULE(sctop) {
  int argc;
  char **argv;
  SC_CTOR(sctop) {
    sc_main(argc, argv);
  }
};

SC_MODULE_EXPORT(sctop)
