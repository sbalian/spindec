// See SpinInteraction.h for description.
// Seto Balian, November 26, 2013

#include "SpinInteraction.h"

SpinInteraction::SpinInteraction()
{
  set_strength(0.0);
  Named::set_class_name("SpinInteractionType");
}

SpinInteraction::SpinInteraction(const double strength)
{
  set_strength(strength);
  Named::set_class_name("SpinInteractionType");
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
