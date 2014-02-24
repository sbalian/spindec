// See IsingHyperfine.h for description.
// Seto Balian, Feb 24, 2014

#include "IsingHyperfine.h"

namespace SpinDecoherence
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
    const SpinVector& spins, const SpinBasis& basis,
    const unsigned int spin_label1, const unsigned int spin_label2) const
{
  SpinInteraction::fill_ising_flipflop(hamiltonian,spins,basis,
      spin_label1,spin_label2,true,cdouble(0.5,0.0));// Ising only
                                                     // set to true
  return;
}

} // namespace SpinDecoherence
