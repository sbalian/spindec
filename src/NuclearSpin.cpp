// See NuclearSpin.h for description.
// Seto Balian, Mar 5, 2014

#include "NuclearSpin.h"

namespace SpinDecoherence
{

NuclearSpin::NuclearSpin() :
  Spin()
{/**/}

NuclearSpin::NuclearSpin(const double quantum_number,
    const double gyromagnetic_ratio,
    const ThreeVector & position,
    const Eigen::VectorXcd & state_vector) :
  Spin(quantum_number, gyromagnetic_ratio,position,state_vector)
{/**/}

NuclearSpin::NuclearSpin(const double quantum_number,
    const double gyromagnetic_ratio) : Spin(quantum_number,gyromagnetic_ratio)
{/**/}

} // namespace SpinDecoherence
