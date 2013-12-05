#ifndef NUCLEARSPIN_H_
#define NUCLEARSPIN_H_

// Nuclear spin
//
// Nothing special for now, just Spin ...
//
// Seto Balian, Dec 5, 2013

#include "Spin.h"

class NuclearSpin : public Spin
{

public:
  NuclearSpin();
  NuclearSpin(const double quantum_number, const double gyromagnetic_ratio);

};

#endif // NUCLEARSPIN_H_
