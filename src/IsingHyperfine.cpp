// See IsingHyperfine.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/IsingHyperfine.h"

namespace SpinDec
{

IsingHyperfine::IsingHyperfine() : Hyperfine()
{
}

IsingHyperfine::IsingHyperfine(
    const HyperfineParameters& parameters) :
        Hyperfine(parameters)
{
}

IsingHyperfine::IsingHyperfine(const double strength) :
        Hyperfine(strength)
{
}

void IsingHyperfine::fill(Eigen::MatrixXcd* hamiltonian,
    const SpinParametersVector& spin_parameters_vector, const SpinBasis& basis,
    const UInt spin_label1, const UInt spin_label2) const
{
  SpinInteraction::fill_ising_flipflop(
      hamiltonian,spin_parameters_vector,basis,
      spin_label1,spin_label2,true,CDouble(0.5,0.0));// Ising only
                                                     // set to true
  return;
}

} // namespace SpinDec
