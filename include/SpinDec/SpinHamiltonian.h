#ifndef SPINHAMILTONIAN_H_
#define SPINHAMILTONIAN_H_

// Seto Balian, Jun 25, 2015

// TODO generalize: include time dependence
// TODO explain changes for "update position" method

#include <string>

#include "SpinDec/SpinOperator.h"

#include "SpinDec/SpinInteractionGraph.h"

#include "SpinDec/UniformMagneticField.h"


namespace SpinDec
{

/**
 * \brief Effective spin Hamiltonian built from a spin interaction graph.
 * 
 * Can diagonalize and get unitary time evolution matrix.
 * No time dependence in Hamiltonian.
 * Units: M rad s\f$^{-1}\f$.
 * 
 */
class SpinHamiltonian : public SpinOperator
{
private:
  UniformMagneticField field_;
  SpinInteractionGraph graph_;
  
  /**
   * \brief Fill diagonal elements with
   *        \f$ \gamma B m \f$.
   *        
   *  \f$B\f$-field strength is for all spins in the graph.
   *  
   */
  void fill_zeeman();
  
  /// Fill elements for all spin interactions.
  void fill_interactions();
    
  /// For each vertex, there is a Zeeman Hamiltonian. Store these.
  vector<ComplexMatrix> zeeman_terms_;
  /// For each edge, there is an interaction Hamiltonian. Store these.
  vector<ComplexMatrix> interaction_terms_;
  /// Sets to zero.
  void init_terms();
  
  /// Summed Zeeman Hamiltonian.
  ComplexMatrix zeeman_hamiltonian_;
  /// Summed interaction Hamiltonian.
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
