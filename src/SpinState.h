#ifndef SPINSTATE_H_
#define SPINSTATE_H_

// SpinState
//
// Quantum spin state in the Zeeman basis.
//
// Seto Balian, Dec 5, 2013

#include <Eigen/Dense>

#include "SpinBasis.h"

class SpinState
{
private:
  
  Eigen::VectorXcd state_;
  SpinBasis basis_;
  
  void quit_if_dimension_mismatch() const;
  
public:
  SpinState();
  SpinState(const Eigen::VectorXcd & state, const SpinBasis & basis);
  
  Eigen::VectorXcd get_state() const;
  SpinBasis get_basis() const;
  
  void set_state(const Eigen::VectorXcd & state);
  
  // States: tensor product ^, Bases: combine ^ (like tensor product)
  SpinState operator^(const SpinState & rhs);
  
  unsigned int dimension() const;
  
};

#endif // SPINSTATE_H_
