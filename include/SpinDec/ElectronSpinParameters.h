#ifndef ELECTRONSPINPARAMETERS_H_
#define ELECTRONSPINPARAMETERS_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinHalfParameters.h"

namespace SpinDec
{

/**
 * \brief Parameters for an electron spin.
 * 
 * Gyromagnetic ratio of the free electron by default.
 * 
 */
class ElectronSpinParameters : public SpinHalfParameters
{
public:
  
  /// Free electron gyromagnetic ratio.
  ElectronSpinParameters();
  explicit ElectronSpinParameters(const double gyromagnetic_ratio);

};

} // namespace SpinDec

#endif // ELECTRONSPINPARAMETERS_H_
