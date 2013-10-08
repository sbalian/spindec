// See Spin.h for description.
// Seto Balian 08/10/2013

#include "Spin.h"

#include <Eigen/Dense>


Spin::Spin()
{
  set_quantum_number(0.0);
  set_gyromagnetic_ratio(0.0);
  set_position(Eigen::Vector3d::Zero());
}

Spin::Spin(const double quantum_number,
           const double gyromagnetic_ratio,
           const Eigen::Vector3d & position)
{
  set_quantum_number(quantum_number);
  set_gyromagnetic_ratio(gyromagnetic_ratio);
  set_position(position);
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


