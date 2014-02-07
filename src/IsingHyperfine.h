#ifndef ISINGHYPERFINE_H_
#define ISINGHYPERFINE_H_

// IsingHyperfine
//
// Like Hyperfine but fill method ignores (1/2) A [S+I- + S-I+]
// in H_A = A Sz Iz + (1/2) A [S+I- + S-I+].
//
// Seto Balian, Feb 7, 2014

#include "Hyperfine.h"

namespace SpinDecoherence
{

class IsingHyperfine : public Hyperfine
{
  IsingHyperfine();
  IsingHyperfine(const ElectronSpin & electron,
                  const NuclearSpin & nucleus,
                  const UniformMagneticField & field,
                  const HyperfineParameters & parameters);

  explicit IsingHyperfine(const double strength);

  virtual void fill(Eigen::MatrixXcd * hamiltonian,
                   const SpinVector & spins,
                   const SpinBasis & basis,
                   const unsigned int spin_label1,
                   const unsigned int spin_label2) const;
  
};

} // namespace SpinDecoherence

#endif // ISINGHYPERFINE_H_
