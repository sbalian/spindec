#ifndef ELECTRONSPIN_H_
#define ELECTRONSPIN_H_

// Electron spin
//
// Spin with fixed quantum number 1/2 and hence multiplicity (= 2).
// Gyromagnetic ratio is for the free electron by default.
//
// Seto Balian, Mar 24, 2014

#include "SpinDec/Spin.h"

namespace SpinDec
{

class ElectronSpin : public Spin
{

public:

  ElectronSpin();
  ElectronSpin(const double gyromagnetic_ratio);

};

} // namespace SpinDec

#endif // ELECTRONSPIN_H_
