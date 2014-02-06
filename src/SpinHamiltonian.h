#ifndef SPINHAMILTONIAN_H_
#define SPINHAMILTONIAN_H_

// SpinHamiltonian
//
// Effective spin Hamiltonian built from a spin interaction graph.
// Can diagonalize and get unitary time evolution matrix.
// No time dependence in Hamiltonian. TODO generalize
// Units: M rad s-1.
//
// Seto Balian, Feb 6, 2014

#include <string>

#include "SpinOperator.h"

#include "SpinInteractionGraph.h"
#include "HermitianEigenspectrum.h"

#include "UniformMagneticField.h"
#include "SpinBasis.h"

#include <Eigen/Dense>

namespace SpinDecoherence
{

class SpinHamiltonian : public SpinOperator
{
private:

  const UniformMagneticField field_;

  // build a combined (like tensor product) SpinBasis and return it
  SpinBasis build_basis(const SpinInteractionGraph & graph) const;
  
  // fill diagonal elements with gyromagnetic_ratio*magnetic_quantum_number*
  // field_strength for all spins in the graph
  void fill_zeeman(const SpinInteractionGraph & graph);
  
  // fill elements for all spin interaction
  void fill_interactions(const SpinInteractionGraph & graph);
  
  // fill all matrix elements using interaction graph
  void fill_matrix(const SpinInteractionGraph & graph);
  
public:

  SpinHamiltonian();
  SpinHamiltonian(const SpinInteractionGraph & graph,
      const UniformMagneticField & field);

  void update(const SpinInteractionGraph & graph);
  
  UniformMagneticField get_field() const;
  
  // Unitary matrix
  // U = \sum{n} ( |E_n> exp(- i E_n t) <E_n| )
  // E_n: eigenvalues
  // |E_n>: eigenvectors
  // t: time (real double) units: microseconds (energies in M rad s-1)
  // (for time independent spin Hamiltonians ...)
  Eigen::MatrixXcd evolution_matrix(const HermitianEigenspectrum & spectrum,
      const double time) const;

};

} // namespace SpinDecoherence

#endif // SPINHAMILTONIAN_H_
