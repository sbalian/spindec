// See SpinHamiltonian.h for description.
// Seto Balian, May 27, 2014

#include "SpinDec/SpinHamiltonian.h"
#include "SpinDec/BoostEigen.h"

#include <memory>

#include <complex>

namespace SpinDec
{

// fill diagonal elements with gyromagnetic_ratio*magnetic_quantum_number*
// field_strength for all spins in the graph
void SpinHamiltonian::fill_zeeman(const SpinInteractionGraph& graph)
{
  // fill diagonal elements [M rad s-1]
  
  // loop over diagonal elements
  for (unsigned int i=0; i<get_dimension();i++) {
    // loop over spins in graph
    for (unsigned int j=0;j<graph.num_vertices();j++) {
      add_to_element(i,i,
          get_basis().get_element(i,j)*// magnetic quantum number
          get_field().get_magnitude()*// field strength [T]
          graph.get_spin_parameters(j).get_gyromagnetic_ratio());
                                                       // gyromagnetic ratio
                                                       // [M rad s-1]
    }
  }
  return;
}

// fill elements for all spin interaction
void SpinHamiltonian::fill_interactions(const SpinInteractionGraph & graph)
{  
  // Loop over edges
  for (unsigned int i=0;i<graph.num_edges();i++) {
    std::auto_ptr<SpinInteraction> interaction_ptr = graph.get_interaction(i);
    if (!interaction_ptr->strength_preset()) { // calculate only if strength
                                               // NOT preset
      interaction_ptr -> calculate(
          graph.get_edge(i).get_vertex1().get_spin_parameters(),
          graph.get_edge(i).get_vertex2().get_spin_parameters(),
          graph.get_edge(i).get_vertex1().get_position(),
          graph.get_edge(i).get_vertex2().get_position(),
                            get_field()); 
    }
    interaction_ptr->fill(&matrix_,graph.spin_parameters_vector(),
        get_basis(),
        graph.get_edge(i).get_vertex1().get_label(),
        graph.get_edge(i).get_vertex2().get_label());
  }
  return;
}

// fill all matrix elements using interaction graph
void SpinHamiltonian::fill_matrix(const SpinInteractionGraph& graph)
{
  fill_zeeman(graph);
  fill_interactions(graph);
  return;
}

SpinHamiltonian::SpinHamiltonian() : SpinOperator(),
    field_(UniformMagneticField())
{
}

SpinHamiltonian::SpinHamiltonian(const SpinInteractionGraph& graph,
    const UniformMagneticField & field) :
    SpinOperator(graph.get_basis()),
    field_(field)
{
  fill_matrix(graph);
}

void SpinHamiltonian::update(const SpinInteractionGraph& graph)
{
  // TODO
  return;
}

UniformMagneticField SpinHamiltonian::get_field() const
{
  return field_;
}

ComplexMatrix SpinHamiltonian::evolution_matrix(
    const ComplexMatrix & eigenvectors,
    const RealVector & eigenvalues,
    const double time) const
{
  return BoostEigen::unitarySpectralDecomposition(
                       eigenvectors,
                       BoostEigen::exp( eigenvalues.cast< CDouble >() * 
                                        std::complex<double>(0.0,-time) ) 
                                                 );
}


} // namespace SpinDec
