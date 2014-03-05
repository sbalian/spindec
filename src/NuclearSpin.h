#ifndef NUCLEARSPIN_H_
#define NUCLEARSPIN_H_

// Nuclear spin
//
// Nothing special for now, just Spin ...
//
// Seto Balian, Mar 5, 2014

#include "Spin.h"

namespace SpinDecoherence
{

class NuclearSpin : public Spin
{

public:
  
  NuclearSpin();
  NuclearSpin(const double quantum_number,
       const double gyromagnetic_ratio,
       const ThreeVector & position,
       const Eigen::VectorXcd & state_vector);  
  NuclearSpin(const double quantum_number,
       const double gyromagnetic_ratio); // zero state vector and position at
                                         // 000

  
};

} // namespace SpinDecoherence

#endif // NUCLEARSPIN_H_
