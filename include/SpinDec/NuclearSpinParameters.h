#ifndef NUCLEARSPINPARAMETERS_H_
#define NUCLEARSPINPARAMETERS_H_

// SpinDec::NuclearSpinParameters
//
// Spin parameters for a nuclear spin.
//
// Seto Balian, May 15, 2014

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinParameters.h"

namespace SpinDec
{

class NuclearSpinParameters : public SpinParameters
{
public:  
  NuclearSpinParameters();
  NuclearSpinParameters(const double quantum_number,
                 const double gyromagnetic_ratio);

};

} // namespace SpinDec

#endif // NUCLEARSPINPARAMETERS_H_
