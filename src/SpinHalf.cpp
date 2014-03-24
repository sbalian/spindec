// See SpinHalf.h for description.
// Seto Balian, Mar 24, 2014

#include "include/SpinDec/SpinHalf.h"

namespace SpinDec
{

SpinHalf::SpinHalf() : Spin(0.5,0.0)
{
}

SpinHalf::SpinHalf(const double gyromagnetic_ratio) :
    Spin(0.5,gyromagnetic_ratio)
{
}

SpinDec::SpinHalf::spin_up() const
{
  ComplexVector spin_up(2);
  
  return VectorXcd
}

SpinDec::SpinHalf::spin_down() const
{
}


} // namespace SpinDec

