#ifndef UNIFORMMAGNETICFIELD_H_
#define UNIFORMMAGNETICFIELD_H_

// UniformMagneticField
//
// Uniform magnetic field parallel to some direction in Cartesian coordinates.
//
// Seto Balian, Feb 6, 2014

#include <Eigen/Dense>

namespace SpinDecoherence
{

class UniformMagneticField
{
private:
  
  double magnitude_; // Tesla
  Eigen::Vector3d direction_; // normalized
  
public:
  
  UniformMagneticField();
  UniformMagneticField(const double magnitude,
      const Eigen::Vector3d & direction);
  
  double get_magnitude() const;
  Eigen::Vector3d get_direction() const;
  
  void set_magnitude(const double magnitude);
  void set_direction(const Eigen::Vector3d & direction);

};

} // namespace SpinDecoherence

#endif // UNIFORMMAGNETICFIELD_H_
