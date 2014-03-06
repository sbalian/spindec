#ifndef UNIFORMMAGNETICFIELD_H_
#define UNIFORMMAGNETICFIELD_H_

// UniformMagneticField
//
// Uniform magnetic field parallel to some direction in Cartesian coordinates.
//
// Seto Balian, Mar 6, 2014

#include <Eigen/Dense>

#include "SpinDec/types.h"

namespace SpinDec
{

class UniformMagneticField
{
private:
  
  double magnitude_; // Tesla
  ThreeVector direction_; // normalized
  
public:
  
  UniformMagneticField();
  explicit UniformMagneticField(const double magnitude);
                                                // null direction (0 0 0)
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
