#ifndef ELECTRONSPIN_H_
#define ELECTRONSPIN_H_

// SpinDec::Electron spin
//
// Spin-1/2 with the gyromagnetic ratio for the free electron by default.
//
// Seto Balian, Mar 28, 2014

#include "SpinDec/SpinHalf.h"

namespace SpinDec
{

class ElectronSpin : public SpinHalf
{
public:
  
  ElectronSpin();
  ElectronSpin(const ComplexVector& state_vector,
               const ThreeVector& position);
  ElectronSpin(const double gyromagnetic_ratio,
               const ComplexVector& state_vector,
               const ThreeVector& position);

};

} // namespace SpinDec

#endif // ELECTRONSPIN_H_
