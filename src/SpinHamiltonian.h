#ifndef SPINHAMILTONIAN_H_
#define SPINHAMILTONIAN_H_

// SpinHamiltonian
//
// Effective spin Hamiltonian built from a spin interaction graph.
// Can diagonalize and get unitary time evolution matrix.
// No time dependence in Hamiltonian. TODO generalize
// Units: M rad s-1.
//
// Seto Balian, Dec 13, 2013

#include <string>

#include "SpinOperator.h"

#include "SpinInteractionGraph.h"
#include "HermitianEigenspectrum.h"

#include "UniformMagneticField.h"

#include <Eigen/Dense>


class SpinHamiltonian : public SpinOperator
{
private:
  
  const UniformMagneticField field_;

  void build_basis(const SpinInteractionGraph & graph) const;
  void fill_matrix(const SpinInteractionGraph & graph) const;

public:

  SpinHamiltonian();
  SpinHamiltonian(const SpinInteractionGraph & graph,
      const UniformMagneticField & field);

  // TODO describe
  void update(const SpinInteractionGraph & graph);
  
  UniformMagneticField get_field() const;
  
  // Unitary matrix
  // U = \sum{n} ( |E_n> exp(- i E_n t) <E_n| )
  // E_n: eigenvalues
  // |E_n>: eigenvectors
  // t: time (real double) units: microseconds (energies in M rad s-1)
  // (for time independent spin Hamiltonians ...)
  Eigen::MatrixXcd evolutionMatrix(const HermitianEigenspectrum & spectrum,
      const double time) const;

};

#endif // SPINHAMILTONIAN_H_
