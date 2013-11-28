#ifndef NUCLEARSPIN_H
#define NUCLEARSPIN_H

// Nuclear spin
//
// Nothing special for now, just Spin ...
//
// Seto Balian, November 28, 2013

#include "Spin.h"

class NuclearSpin : public Spin
{

  NuclearSpin(); // all data members set to zero
  NuclearSpin(const double quantum_number, const double gyromagnetic_ratio);

};

#endif // NUCLEARSPIN_H
