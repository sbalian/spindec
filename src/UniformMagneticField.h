#ifndef UNIFORMMAGNETICFIELD_H_
#define UNIFORMMAGNETICFIELD_H_

// UniformMagneticField
//
// Uniform magnetic field parallel to some direction in Cartesian coordinates.
//
// Seto Balian, Mar 3, 2014

#include <Eigen/Dense>

#include "types.h"

namespace SpinDecoherence
{

class UniformMagneticField
{
private:
  
  double magnitude_; // Tesla
  d3vector direction_; // normalized
  
public:
  
  UniformMagneticField();
  explicit UniformMagneticField(const double magnitude);
                                                // null direction (0 0 0)
                                                // TODO is this safe?
  UniformMagneticField(const double magnitude,
      const d3vector & direction);
  
  double get_magnitude() const;
  d3vector get_direction() const;
  
  void set_magnitude(const double magnitude);
  void set_direction(const d3vector & direction);

};

} // namespace SpinDecoherence

#endif // UNIFORMMAGNETICFIELD_H_
