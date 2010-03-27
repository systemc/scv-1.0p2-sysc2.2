#include "test.cc"

SC_MODULE(sctop) {
  int argc;
  char **argv;
  test thisTest;
  SC_CTOR(sctop) : thisTest("thisTest") { /* empty */ }
};

SC_MODULE_EXPORT(sctop)
