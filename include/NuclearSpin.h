#ifndef NUCLEARSPIN_H
#define NUCLEARSPIN_H

// Nuclear spin
//
// Spin with arbitrary quantum number and gyromagnetic ratio.
//
// Seto Balian, November 27, 2013

#include "Spin.h"

class NuclearSpin : public Spin
{

private:
  
  double quantum_number_;
  
public:

  NuclearSpin();
  NuclearSpin(const double quantum_number, const double gyromagnetic_ratio);

  double get_quantum_number() const;
  void set_quantum_number(const double quantum_number);

  unsigned int multiplicity() const;
  
};

#endif // NUCLEARSPIN_H
