#ifndef SPINSTATE_H_
#define SPINSTATE_H_

// SpinState
//
// Quantum spin state in the Zeeman basis.
//
// Seto Balian, Dec 4, 2013

#include <Eigen/Dense>
#include "SpinBasis.h"

class SpinState
{
private:
  
  Eigen::VectorXcd state_;
  SpinBasis basis_;
  
  void quit_if_dimension_mismatch() const;
  
public:
  SpinState(); // empty basis and empty state
  SpinState(const Eigen::VectorXcd & state, const SpinBasis & basis);
  
  Eigen::VectorXcd get_state() const;
  SpinBasis get_basis() const;
  
  // States: tensor product, Bases: combine
  SpinState operator^(const SpinState & rhs);
  
  unsigned int dimension() const;
  
};

#endif // SPINSTATE_H_
