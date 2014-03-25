// See SpinHalf.h for description.
// Seto Balian, Mar 25, 2014

#include "include/SpinDec/SpinHalf.h"

namespace SpinDec
{

SpinHalf::SpinHalf() : Spin(SpinParameters(0.5,0.0),
                            ComplexVector::Zero(2),
                            ThreeVector::Zero())
{
}

SpinHalf::SpinHalf(const double gyromagnetic_ratio,
    const ComplexVector& state_vector,
    const ThreeVector& position) : Spin(
        SpinParameters(0.5,gyromagnetic_ratio),
        state_vector,
        position)
{
}

SpinState SpinHalf::spin_up() const
{
  ComplexVector spin_up_vector(2);
  if (get_parameters().get_gyromagnetic_ratio() >= 0.0 ) {
    spin_up_vector << CDouble(0.0,0.0), CDouble (1.0,0.0);
  } else {
      spin_up_vector << CDouble(1.0,0.0), CDouble (0.0,0.0);

  }
  return SpinState(spin_up_vector,SpinBasis(get_parameters()));
}

SpinState SpinHalf::spin_down() const
{
  ComplexVector spin_down_vector(2);
  if (get_parameters().get_gyromagnetic_ratio() >= 0.0 ) {
    spin_down_vector << CDouble(1.0,0.0), CDouble (0.0,0.0);
  } else {
      spin_down_vector << CDouble(0.0,0.0), CDouble (1.0,0.0);

  }
  return SpinState(spin_down_vector,SpinBasis(get_parameters()));
}

void SpinHalf::set_spin_up()
{
  state_ = spin_up();
}

void SpinHalf::set_spin_down()
{
  state_ = spin_down();
}


} // namespace SpinDec

