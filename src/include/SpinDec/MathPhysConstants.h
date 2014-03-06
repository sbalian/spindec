#ifndef MATHPHYSCONSTANTS_H_
#define MATHPHYSCONSTANTS_H_

// MathPhysConstants
//
// Static methods for mathematical and physical constants.
//
// Seto Balian, Mar 6, 2014

namespace SpinDec
{

class MathPhysConstants
{

public:

  static double pi();

  // Reduced Planck constant, units: J s
  static double reduced_planck();

  // Planck constant, units: J s
  static double planck();

  // Free electron gyromagnetic ratio, units: M rad s-1
  static double electron_gyromagnetic_ratio();
  
};

} // namespace SpinDec

#endif // MATHPHYSCONSTANTS_H_
