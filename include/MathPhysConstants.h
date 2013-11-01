#ifndef MATHPHYSCONSTANTS_H
#define MATHPHYSCONSTANTS_H

// MathPhysConstants
//
// Static methods for mathematical and physical constants.
//
// Seto Balian 01/11/2013


class MathPhysConstants
{

public:

  static double pi();

  // Reduced Plank constant, units: J s
  static double reduced_plank();

  // Plank constant, units: J s
  static double plank();

  // Free electron gyromagnetic ratio, units: M rad s-1
  static double electron_gyromagnetic_ratio();
  
};

#endif // MATHPHYSCONSTANTS_H

