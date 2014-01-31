#ifndef SPININTERACTION_H_
#define SPININTERACTION_H_

// SpinInteraction
//
// Abstract base class for interaction between a pair of spins.
//
// Seto Balian, Jan 31, 2014

#include <Eigen/Dense>

#include "Spin.h"
#include "SpinVector.h"
#include "SpinBasis.h"
#include "UniformMagneticField.h"

#include <complex>

class SpinInteraction
{
protected:

  double strength_; // M rad s-1 (calculated or set)
  double non_spatial_dependence_; // strength_ / "spatial part"
                                  // (so that this is calculated once)

  const Spin spin1_;
  const Spin spin2_;
  
  UniformMagneticField field_;

  // calculate, set, and return
  virtual double calculate_non_spatial_dependence() const = 0;

  SpinInteraction();
  SpinInteraction(const Spin & spin1,
                  const Spin & spin2, const UniformMagneticField & field);

  // if you don't wish to calculate ...
  SpinInteraction(const Spin & spin1,
                  const Spin & spin2, const UniformMagneticField & field,
                  const double strength);
  
  // ISING            + FLIPFLOP
  // strength*S1z S2z + flipflop_form*strength*(S1+ S2- + S1- S2+)
  // flipflop_form is a complex double
  void fill_ising_flipflop(Eigen::MatrixXcd * hamiltonian,
                   const SpinVector & spins,
                   const SpinBasis & basis,
                   const unsigned int spin_label1,
                   const unsigned int spin_label2,
                   const bool ising_only,
                   const std::complex<double> & flipflop_form) const;

public:

  // calculate (also set and return) strength given
  // the positions of spin1 and spin2
  virtual double calculate(const Eigen::Vector3d & position1,
                           const Eigen::Vector3d & position2)  = 0;

  double get_strength() const;
  UniformMagneticField get_field() const;

  // if you don't wish to calculate
  void set_strength(const double strength);

  virtual void fill(Eigen::MatrixXcd * hamiltonian,
                   const SpinVector & spins,
                   const SpinBasis & basis,
                   const unsigned int spin_label1,
                   const unsigned int spin_label2) const = 0;
  
  virtual ~SpinInteraction();

};

#endif // SPININTERACTION_H_
