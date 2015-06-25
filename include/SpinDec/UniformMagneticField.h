#ifndef UNIFORMMAGNETICFIELD_H_
#define UNIFORMMAGNETICFIELD_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/// Uniform magnetic field parallel to some direction in Cartesian coordinates.
class UniformMagneticField
{
private:
  
  /// Tesla.
  double magnitude_;
  /// Normalized.
  ThreeVector direction_;
  
public:
  
  UniformMagneticField();
  
  /// Null direction (0 0 0).
  explicit UniformMagneticField(const double magnitude);
  // TODO is this safe?
  
  UniformMagneticField(const double magnitude,
      const ThreeVector & direction);
  
  double get_magnitude() const;
  ThreeVector get_direction() const;
  
  void set_magnitude(const double magnitude);
  void set_direction(const ThreeVector & direction);

};

} // namespace SpinDec

#endif // UNIFORMMAGNETICFIELD_H_
