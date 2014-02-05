#ifndef ISINGHYPERFINE_H_
#define ISINGHYPERFINE_H_

// IsingHyperfine
//
// Like Hyperfine but fill method ignores (1/2) A [S+I- + S-I+]
// in H_A = A Sz Iz + (1/2) A [S+I- + S-I+].
//
// Seto Balian, Feb 5, 2014

#include "Hyperfine.h"

class IsingHyperfine : public Hyperfine
{
  IsingHyperfine();
  IsingHyperfine(const ElectronSpin & electron,
                  const NuclearSpin & nucleus,
                  const UniformMagneticField & field,
                  const HyperfineParameters & parameters);

  IsingHyperfine(const ElectronSpin & electron,
                  const NuclearSpin & nucleus, const double strength,
                  const UniformMagneticField & field,
                  const HyperfineParameters & parameters);

  virtual void fill(Eigen::MatrixXcd * hamiltonian,
                   const SpinVector & spins,
                   const SpinBasis & basis,
                   const unsigned int spin_label1,
                   const unsigned int spin_label2) const;
  
};

#endif // ISINGHYPERFINE_H_
