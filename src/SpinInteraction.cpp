// See SpinInteraction.h for description.
// Seto Balian, November 27, 2013

#include "SpinInteraction.h"

SpinInteraction::SpinInteraction()
{
  set_strength(0.0);
}

SpinInteraction::SpinInteraction(const double strength)
{
  set_strength(strength);
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
