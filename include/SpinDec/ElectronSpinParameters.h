#ifndef ELECTRONSPINPARAMETERS_H_
#define ELECTRONSPINPARAMETERS_H_

// SpinDec::ElectronSpinParameters
//
// Parameters for an electron spin. Gyromagnetic ratio of the free electron
// by default.
//
// Seto Balian, Nov 6, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinHalfParameters.h"

namespace SpinDec
{

class ElectronSpinParameters : public SpinHalfParameters
{
public:
  
  // Free electron gyromagnetic ratio
  ElectronSpinParameters();
  explicit ElectronSpinParameters(const double gyromagnetic_ratio);

};

} // namespace SpinDec

#endif // ELECTRONSPINPARAMETERS_H_
