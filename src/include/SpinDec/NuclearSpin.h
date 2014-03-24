#ifndef NUCLEARSPIN_H_
#define NUCLEARSPIN_H_

// Nuclear spin
//
// Nothing special for now, just Spin ...
//
// Seto Balian, Mar 24, 2014

#include "SpinDec/Spin.h"

namespace SpinDec
{

class NuclearSpin : public Spin
{

public:
  
  NuclearSpin();
  NuclearSpin(const double quantum_number,
       const double gyromagnetic_ratio);
  
};

} // namespace SpinDec

#endif // NUCLEARSPIN_H_
