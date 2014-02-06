#ifndef SPINOPERATOR_H_
#define SPINOPERATOR_H_

// SpinOperator
//
// Quantum spin operator in the Zeeman basis.
//
// Seto Balian, Feb 6, 2014

#include <Eigen/Dense>
#include <complex>

#include "SpinBasis.h"
#include "MatrixRepresentation.h"

namespace SpinDecoherence
{

class SpinOperator : public MatrixRepresentation
{
protected:

  Eigen::MatrixXcd matrix_;  
  virtual void quit_if_dimension_mismatch() const;
  
public:
  SpinOperator();
  SpinOperator(const Eigen::MatrixXcd & matrix, const SpinBasis & basis);
  explicit SpinOperator(const SpinBasis & basis); // zero matrix

  Eigen::MatrixXcd get_matrix() const;
  void set_matrix(const Eigen::MatrixXcd & matrix);
  
  std::complex<double> get_element(const unsigned int i,
      const unsigned int j) const;
  void set_element(const unsigned int i, const unsigned int j,
      std::complex<double> element);
  
  void add_to_element(const unsigned int i, const unsigned int j,
      std::complex<double> to_add);

  // Operators: tensor product ^, Bases: combine ^ (like tensor product)
  SpinOperator operator^(const SpinOperator & rhs);
  
  virtual void set_zero(); // set all elements to zero

};

} // namespace SpinDecoherence

#endif // SPINOPERATOR_H_
