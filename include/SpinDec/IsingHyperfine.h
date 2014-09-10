#ifndef ISINGHYPERFINE_H_
#define ISINGHYPERFINE_H_

// SpinDec::IsingHyperfine
//
// Like Hyperfine but fill method ignores (1/2) A [S+I- + S-I+]
// in H_A = A Sz Iz + (1/2) A [S+I- + S-I+].
//
// Seto Balian, Mar 28, 2014

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
                   const SpinParametersVector & spin_parameters_vector,
                   const SpinBasis & basis,
                   const UInt spin_label1,
                   const UInt spin_label2) const;
  
};

} // namespace SpinDec

#endif // ISINGHYPERFINE_H_
