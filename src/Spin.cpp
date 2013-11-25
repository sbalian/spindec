// See Spin.h for description.
// Seto Balian 25/11/2013

#include "Spin.h"
#include "BoostEigen.h"

#include <Eigen/Dense>

void Spin::initialize_zeeman_basis() {
  zeeman_basis_.set_basis(Eigen::ArrayXd::Zero(0));
  return;
}


Spin::Spin()
{
  set_quantum_number(0.0);
  set_gyromagnetic_ratio(0.0);
  set_position(Eigen::Vector3d::Zero());
  initialize_zeeman_basis();
  Named::set_class_name("Spin");
}

Spin::Spin(const double quantum_number,
           const double gyromagnetic_ratio,
           const Eigen::Vector3d & position)
{
  set_quantum_number(quantum_number);
  set_gyromagnetic_ratio(gyromagnetic_ratio);
  set_position(position);
  initialize_zeeman_basis();
  Named::set_class_name("Spin");
}

double Spin::get_quantum_number() const
{
  return quantum_number_;
}

double Spin::get_gyromagnetic_ratio() const
{
  return gyromagnetic_ratio_;
}

Eigen::Vector3d Spin::get_position() const
{
  return position_;
}

ZeemanBasis Spin::get_zeeman_basis() const {
  return zeeman_basis_;
}

void Spin::set_quantum_number(const double quantum_number)
{
  quantum_number_ = quantum_number;
  return;
}

void Spin::set_gyromagnetic_ratio(const double gyromagnetic_ratio)
{
  gyromagnetic_ratio_ = gyromagnetic_ratio;
  return;
}

void Spin::set_position(const Eigen::Vector3d & position)
{
  position_ = position;
  return;
}

unsigned int Spin::multiplicity() const
{
  return static_cast<unsigned int>( 2.0*get_quantum_number() + 1.0 );
}

void Spin::add_magnetic_quantum_number_to_zeeman_basis(
                                      const double magnetic_quantum_number) {
  Eigen::ArrayXd basis = zeeman_basis_.get_basis();
  BoostEigen::addElement(basis,magnetic_quantum_number);
  zeeman_basis_.set_basis(basis);
  return;
}

void Spin::build_zeeman_basis() {
  double magnetic_quantum_number = static_cast<double>(get_quantum_number());
  for (unsigned int i=0;i<multiplicity();i++) {
    add_magnetic_quantum_number_to_zeeman_basis(magnetic_quantum_number);
    magnetic_quantum_number -= 1;
  }
  return;
}
