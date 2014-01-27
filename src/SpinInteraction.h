#ifndef SPININTERACTION_H_
#define SPININTERACTION_H_

// SpinInteraction
//
// Abstract base class for interaction between a pair of spins.
//
// Seto Balian, Jan 27, 2014

#include <Eigen/Dense>
#include <string>

#include "Spin.h"
#include "SpinHamiltonian.h"

class SpinInteraction
{
protected:
  
  double strength_; // M rad s-1 (calculated or set)
  double non_spatial_dependence_; // strength_ / "spatial part"
                                  // (so that this is calculated once)
  
  const Spin spin1_;
  const Spin spin2_;

  // calculate, set, and return
  virtual double calculate_non_spatial_dependence() const = 0;

  SpinInteraction();

  SpinInteraction(const Spin & spin1,
                  const Spin & spin2);

  // if you don't wish to calculate ...
  SpinInteraction(const Spin & spin1,
                  const Spin & spin2, const double strength);
  
  // fill the matrix elements of a spin Hamiltonian
  virtual void fill(SpinHamiltonian & hamiltonian) const = 0;

public:

  // calculate (also set and return) strength given
  // the positions of spin1 and spin2
  virtual double calculate(const Eigen::Vector3d & position1,
                           const Eigen::Vector3d & position2)  = 0;

  double get_strength() const;

  // if you don't wish to calculate
  void set_strength(const double strength);

  virtual ~SpinInteraction();

};

#endif // SPININTERACTION_H_
