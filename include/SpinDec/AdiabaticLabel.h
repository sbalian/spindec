#ifndef ADIABATICLABEL_H_
#define ADIABATICLABEL_H_

// SpinDec::AdiabaticLabel
//
// For a spin donor, the adiabatic energy eigenstates are labeled as follows:
//
// |+/-,m>, where m = S + I is an integer, S and I are the electron and nuclear
// spin quantum numbers.
//
// Seto Balian, Sep 10, 2014

#include "SpinDec/typedefs.h"

#include <iostream>

#include "Sign.h"

namespace SpinDec
{

class AdiabaticLabel
{
private:
  Sign sign_;
  int quantum_number_;

public:

  AdiabaticLabel(const Sign& sign, const int quantum_number);

  const Sign& get_sign() const;
  int get_quantum_number() const;

  friend std::ostream& operator<<(std::ostream & os,
      AdiabaticLabel const & label);

};

} // namespace SpinDec

#endif // ADIABATICLABEL_H_
