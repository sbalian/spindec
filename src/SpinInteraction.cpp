// See SpinInteraction.h for description.
// Seto Balian, Dec 6, 2013

#include "SpinInteraction.h"

SpinInteraction::SpinInteraction() :
  spin1_(Spin()),
  spin2_(Spin())
{
  strength_ = 0.0;
  non_spatial_dependence_ = 0.0;
}

SpinInteraction::SpinInteraction(const Spin& spin1, const Spin& spin2) :
    spin1_(spin1),
    spin2_(spin2)
{
  strength_ = 0.0;
  non_spatial_dependence_ = 0.0;
}

SpinInteraction::SpinInteraction(const Spin& spin1, const Spin& spin2,
    const double strength) :
    spin1_(spin1),
    spin2_(spin2)
{
  strength_ = strength;
  non_spatial_dependence_ = 0.0;
}

double SpinInteraction::get_strength() const
{
  return strength_;
}

void SpinInteraction::set_strength(const double strength)
{
  strength_ = strength;
  return;
}

SpinInteraction::~SpinInteraction()
{/**/}
