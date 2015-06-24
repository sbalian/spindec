#ifndef ADIABATICLABEL_H_
#define ADIABATICLABEL_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"

#include <iostream>

#include "Sign.h"

namespace SpinDec
{

/**
 * \brief Adiabatic eigenstates of a spin donor.
 *
 * For a spin donor, the adiabatic energy eigenstates are labeled as follows:
 *
 * \f$\left|\pm,m\right\rangle\f$, where \f$m = S + I\f$ is an integer,
 * \f$S\f$ and \f$I\f$ are the electron and nuclear spin quantum numbers.
 */
class AdiabaticLabel
{

private:
  
  /// Plus or minus.
  Sign sign_;
  
  /// \f$m = S + I\f$.
  int quantum_number_;
  
  
public:

  AdiabaticLabel(const Sign& sign, const int quantum_number);

  const Sign& get_sign() const;
  int get_quantum_number() const;

  /// Print.
  friend std::ostream& operator<<(std::ostream & os,
      AdiabaticLabel const & label);

};

} // namespace SpinDec

#endif // ADIABATICLABEL_H_
