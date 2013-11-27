// See Spin.h for description.
// Seto Balian, November 27, 2013

#include "Spin.h"
#include "BoostEigen.h"

double Spin::get_gyromagnetic_ratio() const
{
  return gyromagnetic_ratio_;
}

void Spin::set_gyromagnetic_ratio(const double gyromagnetic_ratio)
{
  gyromagnetic_ratio_ = gyromagnetic_ratio;
  return;
}
