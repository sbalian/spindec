// Three component vector.
//
// Created  13/03/2012
// Modified 19/09/2012, 20/09/2012, 21/09/2012, 22/09/2012, 09/10/2012, 15/11/2012
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "threevector.hpp"

using namespace std;
  
threevector::threevector() {
  set_x(0.0);
  set_y(0.0);
  set_z(0.0);
}
threevector::threevector(const double x_in, const double y_in, const double z_in) {
  set_x(x_in);
  set_y(y_in);
  set_z(z_in);
}

double threevector::get_x() const {
  return x; 
}
double threevector::get_y() const {
  return y; 
}
double threevector::get_z() const {
  return z; 
}

void threevector::set_x(const double x_in) {
  x = x_in; 
  return;
}
void threevector::set_y(const double y_in) {
  y = y_in;
  return;
}
void threevector::set_z(const double z_in) {
  z = z_in;
  return;
}

double threevector::modSquared() const { // Modulus squared
  return get_x()*get_x() + get_y()*get_y() + get_z()*get_z();
}
double threevector::mod() const { // Modulus
  return sqrt(modSquared()); 
}

threevector threevector::normalised() const {
  return threevector( (*this)*( 1.0/mod() ) );
}

threevector threevector::operator+(const threevector & threevector_to_add) const {
  threevector vout( threevector_to_add.get_x() + get_x() , threevector_to_add.get_y() + get_y() , threevector_to_add.get_z() + get_z() );
  return vout;
}
threevector threevector::operator-(const threevector & threevector_to_subtract) const {
  threevector vout(-threevector_to_subtract.get_x() + get_x(),-threevector_to_subtract.get_y() + get_y(),-threevector_to_subtract.get_z() + get_z());
  return vout;
}
threevector threevector::operator*(const double scalefactor) const {
  threevector vout (get_x()*scalefactor, get_y()*scalefactor, get_z()*scalefactor);
  return vout;
}
double threevector::operator*(const threevector & b) const { // vector dot product a.b
  return b.get_x()*get_x() + b.get_y()*get_y() + b.get_z()*get_z();
}

double threevector::cos_theta(const threevector & a, const threevector & b) { // get cosine of angle between vectors a and b = a.b/ab
  return (a*b) / (a.mod()*b.mod());
}

void threevector::set_zero() {
  set_x( 0.0 );
  set_y( 0.0 );
  set_z( 0.0 );
  return;
}

void threevector::print() const { // Print column vector
  cout << get_x() << endl;
  cout << get_y() << endl;
  cout << get_z() << endl;
  return;
}

void threevector::print(const char c_or_r) const {
  if (c_or_r == 'c') {  // column vector
    print();
    return;
  }
  if (c_or_r == 'r') { // row vector
    cout << get_x() << "\t" << get_y() << "\t" << get_z() << endl;
    return;
  }
  cout << "In threevector::print(char option), option = 'c' OR 'r', for column or row vector." << endl;
  return;
}

double threevector::get_component(const int index) const {
  double component;
  switch (index){
  case 1:
    component = get_x();
    break;
  case 2:
    component = get_y();
    break;
  case 3:
    component = get_z();
    break;
  default:
    component = 0.0;
    cout << "WARNING: In threevector::get_component(int index), index = 1, 2 or 3. Returning 0.0." << endl;
    break;
  }
  return component;

}

double threevector::get_max_abs_comp() const {

// SLOWER!
//  if ( ( abs(get_x()) - abs(get_y()) ) >= 0  ) {
//    if ( abs(get_x()) - abs(get_z()) >=0  ) {
//      return get_x();
//    } else {
//        return get_z();
//      }
//  } else {
//    if ( abs(get_y()) - abs(get_z()) >=0  ) {
//      return get_y();
//    } else {
//        return get_z();
//      }

//    }

  return max ( max ( abs(get_x()) , abs(get_y()) ) , abs(get_z()) );

}


