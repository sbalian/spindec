#ifndef ELECTRONSPIN_H_
#define ELECTRONSPIN_H_

// Electron spin
//
// Spin with fixed quantum number 1/2 and hence multiplicity (= 2).
// Gyromagnetic ratio is for the free electron by default.
//
// Seto Balian, Mar 5, 2014

#include "Spin.h"

namespace SpinDecoherence
{

class ElectronSpin : public Spin
{

public:

  // zero state, zero position, free electron gyromagnetic ratio
  ElectronSpin();
  // zero state, zero position
  ElectronSpin(const double gyromagnetic_ratio);
  
  //free electron gyromagnetic ratio
  ElectronSpin(const ThreeVector & position,
               const Eigen::VectorXcd & state_vector);
  
  ElectronSpin(const double gyromagnetic_ratio,
               const ThreeVector & position,
               const Eigen::VectorXcd & state_vector);

  

};

} // namespace SpinDecoherence

#endif // ELECTRONSPIN_H_
