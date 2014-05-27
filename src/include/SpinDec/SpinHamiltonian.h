#ifndef SPINHAMILTONIAN_H_
#define SPINHAMILTONIAN_H_

// SpinDec::SpinHamiltonian
//
// Effective spin Hamiltonian built from a spin interaction graph.
// Can diagonalize and get unitary time evolution matrix.
// No time dependence in Hamiltonian. TODO generalize
// Units: M rad s-1.
//
// Seto Balian, May 27, 2014

#include <string>

#include "SpinDec/SpinOperator.h"

#include "SpinDec/SpinInteractionGraph.h"

#include "SpinDec/UniformMagneticField.h"

#include <Eigen/Dense>

namespace SpinDec
{

class SpinHamiltonian : public SpinOperator
{
private:

  UniformMagneticField field_;
  
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
  // E_n: eigenvalues (real)
  // |E_n>: eigenvectors
  // t: time (real double) units: microseconds (energies in M rad s-1)
  // (for time independent spin Hamiltonians ...)
  ComplexMatrix evolution_matrix(const ComplexMatrix & eigenvectors,
      const RealVector & eigenvalues,
      const double time) const;
  
};

} // namespace SpinDec

#endif // SPINHAMILTONIAN_H_
