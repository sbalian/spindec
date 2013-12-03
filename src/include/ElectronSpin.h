#ifndef ELECTRONSPIN_H_
#define ELECTRONSPIN_H_

// Electron spin
//
// Spin with fixed quantum number 1/2 and hence multiplicity (= 2).
// Gyromagnetic ratio is for the free electron by default.
//
// Seto Balian, Dec 3, 2013

#include "Spin.h"

class ElectronSpin : public Spin
{

public:

  ElectronSpin();
  ElectronSpin(const double gyromagnetic_ratio);

};

#endif // ELECTRONSPIN_H_
