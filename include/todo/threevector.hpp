#ifndef THREEVECTOR_H
#define THREEVECTOR_H

// Three component vector.
//
// Created  19/10/2011
// Modified 19/09/2012, 20/09/2012, 22/09/2012, 09/10/2012
// Seto Balian
// V1

#include "stdincludes.hpp"

using namespace std;

class threevector
{

private:
  double x,y,z; // Cartesian components

public:
  
  threevector();
  threevector(const double x_in, const double y_in, const double z_in);
  
  double get_x() const;
  double get_y() const;
  double get_z() const;
  
  void set_x(const double x_in);
  void set_y(const double y_in);
  void set_z(const double z_in);
  
  double modSquared() const;
  double mod() const;

  threevector normalised() const;
  
  threevector operator+(const threevector & threevector_to_add) const;
  threevector operator-(const threevector & threevector_to_subtract) const;
  threevector operator*(const double scalefactor) const; // scale
  double operator*(const threevector & b) const; // dot product

  static double cos_theta(const threevector & a, const threevector & b); // get cosine of the angle between two 3-vectors

  void set_zero();
  
  void print() const;
  void print(const char c_or_r) const; // option: column or row
  
  double get_component(const int index) const; // index =1,2,3 for x,y,z

  double get_max_abs_comp() const;

};

#endif // THREEVECTOR_H

