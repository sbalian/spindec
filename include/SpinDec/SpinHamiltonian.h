#ifndef SPINHAMILTONIAN_H_
#define SPINHAMILTONIAN_H_

// SpinDec::SpinHamiltonian
//
// Effective spin Hamiltonian built from a spin interaction graph.
// Can diagonalize and get unitary time evolution matrix.
// No time dependence in Hamiltonian. TODO generalize
// Units: M rad s-1.
//
// TODO explain changes for "update position" method
//
// Seto Balian, Sep 29, 2014

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
  SpinInteractionGraph graph_;
  
  // fill diagonal elements with gyromagnetic_ratio*magnetic_quantum_number*
  // field_strength for all spins in the graph
  void fill_zeeman();
  
  // fill elements for all spin interaction
  void fill_interactions();
    
  // For each vertex, there is a Zeeman Hamiltonian. Store these.
  vector<ComplexMatrix> zeeman_terms_;
  // For each edge, there is an interaction Hamiltonian. Store these.
  vector<ComplexMatrix> interaction_terms_;
  void init_terms(); // sets to zero
  
  // summed zeeman and interaction Hamiltonians
  ComplexMatrix zeeman_hamiltonian_;
  ComplexMatrix interaction_hamiltonian_;

  void sum_zeeman_terms();
  void sum_interaction_terms();
  
  void fill_zeeman(const UInt vertex_label);
  void fill_interaction(const UInt edge_index);

  
public:

  SpinHamiltonian();
  SpinHamiltonian(const SpinInteractionGraph & graph,
      const UniformMagneticField & field);
  
  UniformMagneticField get_field() const;
  const SpinInteractionGraph& get_graph() const;
  
  void update_positions(const UIntArray& vertex_labels,
      const vector<ThreeVector>& positions);
  
};

} // namespace SpinDec

#endif // SPINHAMILTONIAN_H_
