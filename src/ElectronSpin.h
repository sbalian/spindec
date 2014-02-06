#ifndef ELECTRONSPIN_H_
#define ELECTRONSPIN_H_

// Electron spin
//
// Spin with fixed quantum number 1/2 and hence multiplicity (= 2).
// Gyromagnetic ratio is for the free electron by default.
//
// Seto Balian, Feb 6, 2014

#include "Spin.h"

namespace SpinDecoherence
{

class ElectronSpin : public Spin
{

public:

  ElectronSpin();
  explicit ElectronSpin(const double gyromagnetic_ratio);

};

} // namespace SpinDecoherence

#endif // ELECTRONSPIN_H_
