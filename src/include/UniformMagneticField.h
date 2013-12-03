#ifndef UNIFORMMAGNETICFIELD_H_
#define	UNIFORMMAGNETICFIELD_H_

// UniformMagneticField
//
// Uniform magnetic field parallel to some direction in Cartesian coordinates.
//
// Seto Balian, Dec 3, 2013

#include <Eigen/Dense>

class UniformMagneticField
{

private:
  
  double magnitude_;
  Eigen::Vector3d direction_;
  
public:
  
  UniformMagneticField();
  UniformMagneticField(const double magnitude,
                       const Eigen::Vector3d & direction);
  
  double get_magnitude() const;
  Eigen::Vector3d get_direction() const;
  
  void set_magnitude(const double magnitude);
  void set_direction(const Eigen::Vector3d & direction);
  

};

#endif	 // UNIFORMMAGNETICFIELD_H_
