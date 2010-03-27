//  -*- C++ -*- <this line is for emacs to recognize it as C++ code>
/*****************************************************************************
 constraints.h -- 
  
 Define a constraint class to illustrate notion of dependent variables
 and explain use_constraint() and next() on dependent object semantics.
  
 *****************************************************************************/

#ifndef _CONSTRAINT_H
#define _CONSTRAINT_H

class dependent_integer_constraints : public scv_constraint_base {
public:
  scv_smart_ptr<int> ivar;
  scv_smart_ptr<int> jvar;
public:
  SCV_CONSTRAINT_CTOR(dependent_integer_constraints) {
    SCV_CONSTRAINT(ivar() >= 3 && ivar() <= 12);
    SCV_CONSTRAINT(jvar() >= 3 && jvar() <= 12);
    SCV_SOFT_CONSTRAINT(ivar() > jvar() );
  }
};

inline void print_constraint(dependent_integer_constraints& c)
{
  cout << "  ivar: " << *c.ivar << " jvar: " << *c.jvar << endl;
}

#endif // _CONSTRAINT_H
