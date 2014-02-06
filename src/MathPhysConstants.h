#ifndef MATHPHYSCONSTANTS_H_
#define MATHPHYSCONSTANTS_H_

// MathPhysConstants
//
// Static methods for mathematical and physical constants.
//
// Seto Balian, Feb 6, 2014

namespace SpinDecoherence
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

} // namespace SpinDecoherence

#endif // MATHPHYSCONSTANTS_H_
