// See SpinInteractionVertex.h for description.
// Seto Balian, Mar 6, 2014

#include "SpinDec/SpinInteractionVertex.h"

namespace SpinDec
{

SpinInteractionVertex::SpinInteractionVertex() :
    label_(0),spin_(Spin())
{/**/}

SpinInteractionVertex::SpinInteractionVertex(
    const unsigned int label, const Spin& spin) :
        label_(label), spin_(spin)
{
}

unsigned int SpinInteractionVertex::get_label() const
{
  return label_;
}

const Spin& SpinInteractionVertex::get_spin() const
{
  return spin_;
}

void SpinInteractionVertex::set_spin(const Spin& spin)
{
  spin_ = spin;
  return;
}

} // namespace SpinDec

