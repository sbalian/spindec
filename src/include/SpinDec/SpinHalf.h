#ifndef SPINHALF_H_
#define SPINHALF_H_

// SpinDec::SpinHalf
//
// Spin-1/2.
//
// Seto Balian, Mar 28, 2014

#include "SpinDec/Spin.h"
#include "SpinDec/typedefs.h"

#include <Eigen/Dense>

namespace SpinDec
{

class SpinHalf : public Spin
{
public:

  SpinHalf();
  SpinHalf(const double gyromagnetic_ratio,
           const ComplexVector& state_vector,
           const ThreeVector& position);
  
  SpinState spin_up()  const;
  SpinState spin_down() const;
  
  void set_spin_up();
  void set_spin_down();
  
};

} // namespace SpinDec

#endif // SPINHALF_H_
