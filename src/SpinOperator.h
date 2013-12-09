#ifndef SPINOPERATOR_H_
#define SPINOPERATOR_H_

// SpinOperator
//
// Quantum spin operator in the Zeeman basis.
//
// Seto Balian, Dec 9, 2013

#include <Eigen/Dense>

#include "SpinBasis.h"
#include "MatrixRepresentation.h"
#include "Eigenspectrum.h"

class SpinOperator : public MatrixRepresentation
{
private:
  
  Eigen::MatrixXcd matrix_;
  virtual void quit_if_dimension_mismatch() const;
  
  // TODO add eigenspectrum ...
  
  
public:
  SpinOperator();
  SpinOperator(const Eigen::MatrixXcd & matrix, const SpinBasis & basis);
  
  Eigen::MatrixXcd get_matrix() const;
  void set_matrix(const Eigen::MatrixXcd & matrix);

  // Operators: tensor product ^, Bases: combine ^ (like tensor product)
  SpinOperator operator^(const SpinOperator & rhs);
  
  virtual void set_zero(); // set all elements to zero

};

#endif // SPINOPERATOR_H_
