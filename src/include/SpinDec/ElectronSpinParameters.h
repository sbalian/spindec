#ifndef ELECTRONSPINPARAMETERS_H_
#define ELECTRONSPINPARAMETERS_H_

// SpinDec::ElectronSpinParameters
//
// Parameters for an electron spin. Gyromagnetic ratio of the free electron
// by default.
//
// Seto Balian, Mar 31, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinParameters.h"

namespace SpinDec
{

class ElectronSpinParameters : public SpinParameters
{
public:
  ElectronSpinParameters(); // free electron gyromagnetic ratio
  ElectronSpinParameters(const double gyromagnetic_ratio);

};

} // namespace SpinDec

#endif // ELECTRONSPINPARAMETERS_H_
