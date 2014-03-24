#ifndef SPINHALF_H_
#define SPINHALF_H_

// SpinHalf
//
// Spin-1/2.
//
// Seto Balian, Mar 24, 2014

#include "SpinDec/Spin.h"
#include "SpinDec/typedefs.h"

#include <Eigen/Dense>

namespace SpinDec
{

class SpinHalf : public Spin
{
public:

  SpinHalf();
  SpinHalf(const double gyromagnetic_ratio);
  
  ComplexVector spin_up()  const;
  ComplexVector spin_down() const;
  
  
  
};

} // namespace SpinDec

#endif // SPINHALF_H_
