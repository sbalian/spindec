#ifndef HYPERFINE_H_
#define HYPERFINE_H_

// Hyperfine
//
// Calculates the hyperfine interaction between an electron and a nucleus in
// a lattice using the Kohn-Luttinger electronic wavefunction.
//
// TODO Describe calculation, mention Fermi contact
//
// Units: M rad s-1
//
// From: arXiv:cond-mat/0211567 (Phys. Rev. B 68, 115322 (2003))
//
// Seto Balian, Jan 31, 2014

#include "SpinInteraction.h"
#include "UniformMagneticField.h"
#include "SpinBasis.h"

#include "ElectronSpin.h"
#include "NuclearSpin.h"

#include "HyperfineParameters.h"

#include <Eigen/Dense>

class Hyperfine : public SpinInteraction
{
private:

  HyperfineParameters parameters_;
  virtual double calculate_non_spatial_dependence() const;
  
  double envelope_function(const unsigned int index,
      const Eigen::Vector3d & separation) const;
  double n_parameter() const;
  double n_times_a() const;
  double n_times_b() const;
  double scaled_probability_density(const Eigen::Vector3d & separation) const;

public:
  
  Hyperfine();
  Hyperfine(const ElectronSpin & electron,
                  const NuclearSpin & nucleus,
                  const UniformMagneticField & field,
                  const HyperfineParameters & parameters);

  Hyperfine(const ElectronSpin & electron,
                  const NuclearSpin & nucleus, const double strength,
                  const UniformMagneticField & field,
                  const HyperfineParameters & parameters);

  virtual double calculate(const Eigen::Vector3d & position1,
                           const Eigen::Vector3d & position2);

  virtual void fill(Eigen::MatrixXcd * hamiltonian,
                   const SpinVector & spins,
                   const SpinBasis & basis,
                   const unsigned int spin_label1,
                   const unsigned int spin_label2) const;

};

#endif // HYPERFINE_H_
