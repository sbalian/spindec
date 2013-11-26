// See Spin.h for description.
// Seto Balian, November 26, 2013

#include "Spin.h"
#include "BoostEigen.h"

#include <Eigen/Dense>


Spin::Spin()
{
  set_quantum_number(0.0);
  set_gyromagnetic_ratio(0.0);
  set_position(Eigen::Vector3d::Zero());
  Named::set_class_name("Spin");
}

Spin::Spin(const double quantum_number,
           const double gyromagnetic_ratio,
           const Eigen::Vector3d & position)
{
  set_quantum_number(quantum_number);
  set_gyromagnetic_ratio(gyromagnetic_ratio);
  set_position(position);
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

SingleSpinZeemanBasis Spin::get_zeeman_basis() const {
  return zeeman_basis_;
}

Eigen::VectorXcd Spin::get_state() const
{
  return state_;
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

void Spin::set_zeeman_basis(const SingleSpinZeemanBasis & zeeman_basis)
{
  zeeman_basis_ = zeeman_basis;
  return;
}

void Spin::set_state(const Eigen::VectorXcd & state)
{
  state_ = state;
  return;
}

void Spin::build_zeeman_basis() {
  zeeman_basis_.build(multiplicity(),get_quantum_number());
  return;
}

void Spin::add_magnetic_quantum_number(const double magnetic_quantum_number) {
  zeeman_basis_.add_magnetic_quantum_number(magnetic_quantum_number);
  return;
}

unsigned int Spin::multiplicity() const
{
  return static_cast<unsigned int>( 2.0*get_quantum_number() + 1.0 );
}
