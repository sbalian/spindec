// See SpinInteractionVertex.h for description.
// Seto Balian, Mar 28, 2014

#include "SpinDec/SpinInteractionVertex.h"

namespace SpinDec
{

SpinInteractionVertex::SpinInteractionVertex() :
    label_(0),
    spin_parameters_(SpinParameters()),
    basis_(SpinBasis(SpinParameters())),
    position_(ThreeVector::Zero())
{/**/}

SpinInteractionVertex::SpinInteractionVertex(
    UInt label, const SpinParameters& spin_parameters,
    const ThreeVector& position) :
        label_(label),
        spin_parameters_(spin_parameters),
        basis_(SpinBasis(spin_parameters)),
        position_(position)
{
}

SpinInteractionVertex::SpinInteractionVertex(const UInt label,
                      const SpinParameters& spin_parameters,
                      const SpinBasis& basis,
                      const ThreeVector & position) :
label_(label),
spin_parameters_(spin_parameters),
basis_(basis),
position_(position)
{
}

unsigned int SpinInteractionVertex::get_label() const
{
  return label_;
}

const SpinParameters& SpinInteractionVertex::get_spin_parameters() const
{
  return spin_parameters_;
}

const SpinBasis& SpinInteractionVertex::get_basis() const
{
  return basis_;
}

const ThreeVector& SpinInteractionVertex::get_position() const
{
  return position_;
}

} // namespace SpinDec

