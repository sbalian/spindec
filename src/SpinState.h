#ifndef SPINSTATE_H_
#define SPINSTATE_H_

// SpinState
//
// Quantum spin state in the Zeeman basis.
//
// Seto Balian, Dec 9, 2013

#include <Eigen/Dense>

#include "SpinBasis.h"
#include "MatrixRepresentation.h"

class SpinState : public MatrixRepresentation
{
private:
  
  Eigen::VectorXcd state_;
  virtual void quit_if_dimension_mismatch() const;

  
public:
  SpinState();
  SpinState(const Eigen::VectorXcd & state, const SpinBasis & basis);
  
  Eigen::VectorXcd get_state() const;
  void set_state(const Eigen::VectorXcd & state);
  
  // States: tensor product ^, Bases: combine ^ (like tensor product)
  SpinState operator^(const SpinState & rhs);
  
  virtual void set_zero(); // set all elements to zero
    
};

#endif // SPINSTATE_H_
