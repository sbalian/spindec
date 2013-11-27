#ifndef ELECTRONSPIN_H
#define ELECTRONSPIN_H

// Electron spin
//
// Spin with fixed quantum number 1/2.
// Gyromagnetic ratio is for the free electron by default.
//
// Seto Balian, November 27, 2013

#include "Spin.h"
#include <Eigen/Dense>

class ElectronSpin : public Spin
{

public:

  ElectronSpin();
  ElectronSpin(const double gyromagnetic_ratio);

  double get_quantum_number() const; // = 0.5

  unsigned int multiplicity() const; // = 2

};

#endif // ELECTRONSPIN_H
