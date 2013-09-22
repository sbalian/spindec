// Seto Balian 19/05/2013

#include "Named.h"
#include "Spin.h"
#include <iostream>
#include <string>

#include "MathPhysConstants.h"

#include <Eigen/Dense>

#include "ExtendEigen.h"

Spin::Spin() : Named()
{
  setSpinQuantumNumber(0.0);
  setGyromagneticRatio(0.0);
  setPosition(Eigen::Vector3d::Zero());
}

Spin::Spin(const std::string & name, const double spinQuantumNumber,
           const double gyromagneticRatio, const Eigen::Vector3d & position)
          : Named(name)
{
  setSpinQuantumNumber(spinQuantumNumber);
  setGyromagneticRatio(gyromagneticRatio);
  setPosition(position);
}

double Spin::getSpinQuantumNumber() const
{
  return spinQuantumNumber_;
}

double Spin::getGyromagneticRatio() const
{
  return gyromagneticRatio_;
}

Eigen::Vector3d Spin::getPosition() const
{
  return position_;
}


void Spin::setSpinQuantumNumber(const double spinQuantumNumber)
{
  spinQuantumNumber_ = spinQuantumNumber;
  return;
}

void Spin::setGyromagneticRatio(const double gyromagneticRatio)
{
  gyromagneticRatio_ = gyromagneticRatio;
  return;
}

void Spin::setPosition(const Eigen::Vector3d & position)
{
  position_ = position;
  return;
}

unsigned int Spin::multiplicity() const
{
  return static_cast<unsigned int>( 2.0*getSpinQuantumNumber() + 1.0 );
}

double Spin::dipolar(const Spin & interactingSpin,
                 const Eigen::Vector3d & magneticFieldDirection) const {

  // Vacuum permeability / 4pi = 1.0e-7
  double prefactor = 1.0e-7*getGyromagneticRatio()*
                     interactingSpin.getGyromagneticRatio()*
                     MathPhysConstants::hBar()*1.0e6;
                     // units M rad s-1 m^3

  double cosThetaSq = std::pow(
                  ExtendEigen::cosineAngle(getPosition(),
                                         interactingSpin.getPosition()),2.0);

  double normR = (getPosition() - interactingSpin.getPosition()).norm();

  return prefactor*(1.0 - 3.0*cosThetaSq)
                    /std::pow(normR*1.0e-10,3.0); // units M rad s-1
                              // Angstroms

}


void Spin::print() const
{
  std::cout << "Spin: " << getName() << std::endl;
  std::cout << "Spin quantum number = " << getSpinQuantumNumber() << std::endl;
  std::cout << "Gyromagnetic ratio = " << getGyromagneticRatio() << std::endl;
  std::cout << "Position = " << getPosition() << std::endl;
  std::cout << std::endl;
  return;
}


