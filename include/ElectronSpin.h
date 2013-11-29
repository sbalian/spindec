#ifndef ELECTRONSPIN_H
#define ELECTRONSPIN_H

// Electron spin
//
// Spin with fixed quantum number 1/2 and hence multiplicity (= 2).
// Gyromagnetic ratio is for the free electron by default.
//
// Seto Balian, November 29, 2013

#include "Spin.h"

class ElectronSpin : public Spin
{

public:

  ElectronSpin();
  ElectronSpin(const double gyromagnetic_ratio);

};

#endif // ELECTRONSPIN_H
