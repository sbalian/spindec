#ifndef NUCLEARSPIN_H_
#define NUCLEARSPIN_H_

// Nuclear spin
//
// Nothing special for now, just Spin ...
//
// Seto Balian, Feb 6, 2014

#include "Spin.h"

namespace SpinDecoherence
{

class NuclearSpin : public Spin
{

public:
  NuclearSpin();
  NuclearSpin(const double quantum_number, const double gyromagnetic_ratio);

};

} // namespace SpinDecoherence

#endif // NUCLEARSPIN_H_
