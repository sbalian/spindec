#ifndef ELECTRONSPINPARAMETERS_H_
#define ELECTRONSPINPARAMETERS_H_

// SpinDec::ElectronSpinParameters
//
// Parameters for an electron spin. Gyromagnetic ratio of the free electron
// by default.
//
// Seto Balian, Apr 1, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinParameters.h"

namespace SpinDec
{

class ElectronSpinParameters : public SpinParameters
{
public:
  
  // Free electron gyromagnetic ratio
  ElectronSpinParameters();
  
  ElectronSpinParameters(const double gyromagnetic_ratio);

};

} // namespace SpinDec

#endif // ELECTRONSPINPARAMETERS_H_
