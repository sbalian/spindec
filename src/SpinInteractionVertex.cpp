// See SpinInteractionVertex.h for description.
// Seto Balian, Feb 20, 2014

#include "SpinInteractionVertex.h"

namespace SpinDecoherence
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

} // namespace SpinDecoherence

