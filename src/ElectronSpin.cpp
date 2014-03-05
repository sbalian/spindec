// See ElectronSpin.h for description.
// Seto Balian, Mar 5, 2014

#include "ElectronSpin.h"
#include "MathPhysConstants.h"

namespace SpinDecoherence
{

const double free_gamma_e = MathPhysConstants::electron_gyromagnetic_ratio();

ElectronSpin::ElectronSpin() :
    Spin(0.5,free_gamma_e)
{/**/}

ElectronSpin::ElectronSpin(const double gyromagnetic_ratio) :
        Spin(0.5,gyromagnetic_ratio)
{/**/}

ElectronSpin::ElectronSpin(const ThreeVector & position,
             const Eigen::VectorXcd & state_vector) :
      Spin(0.5,free_gamma_e,position,state_vector)
{/**/}


ElectronSpin::ElectronSpin(const double gyromagnetic_ratio,
             const ThreeVector & position,
             const Eigen::VectorXcd & state_vector) :
   Spin(0.5,gyromagnetic_ratio,position,state_vector)
{/**/}


} // namespace SpinDecoherence
