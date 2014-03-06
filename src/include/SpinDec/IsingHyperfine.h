#ifndef ISINGHYPERFINE_H_
#define ISINGHYPERFINE_H_

// IsingHyperfine
//
// Like Hyperfine but fill method ignores (1/2) A [S+I- + S-I+]
// in H_A = A Sz Iz + (1/2) A [S+I- + S-I+].
//
// Seto Balian, Mar 6, 2014

#include "SpinDec/Hyperfine.h"

namespace SpinDec
{

class IsingHyperfine : public Hyperfine
{

public:
  
  IsingHyperfine();
  IsingHyperfine(const double strength);
  IsingHyperfine(const HyperfineParameters & parameters);

  virtual void fill(ComplexMatrix * hamiltonian,
                   const SpinVector & spins,
                   const SpinBasis & basis,
                   const unsigned int spin_label1,
                   const unsigned int spin_label2) const;
  
};

} // namespace SpinDec

#endif // ISINGHYPERFINE_H_
