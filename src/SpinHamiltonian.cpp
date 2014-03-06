// See SpinHamiltonian.h for description.
// Seto Balian, Mar 6, 2014

#include "SpinDec/SpinHamiltonian.h"
#include "SpinDec/BoostEigen.h"

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
          graph.get_spin(j).get_gyromagnetic_ratio()); // gyromagnetic ratio
                                                       // [M rad s-1]
    }
  }
  return;
}

// fill elements for all spin interaction
void SpinHamiltonian::fill_interactions(const SpinInteractionGraph & graph)
{
  
  SpinInteraction* interaction_ptr = NULL;
  
  // Loop over edges
  for (unsigned int i=0;i<graph.num_edges();i++) {
    interaction_ptr = graph.get_interaction(i);
    if (!interaction_ptr->strength_preset()) { // calculate only if strength
                                               // NOT preset
      interaction_ptr -> calculate(graph.get_edge(i).get_vertex1().get_spin(),
                                   graph.get_edge(i).get_vertex2().get_spin(),
                                   get_field()); 
    }
    interaction_ptr->fill(&matrix_,graph.get_spins(),
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
    SpinOperator(graph.build_basis()),
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

Eigen::MatrixXcd SpinHamiltonian::evolution_matrix(
    const HermitianEigenspectrum & spectrum, const double time) const
{
  return BoostEigen::unitarySpectralDecomposition(
                       spectrum.get_eigenvectors(),
                       BoostEigen::exp( spectrum.get_eigenvalues() * 
                                        std::complex<double>(0.0,-time) ) 
                                                 );
}


} // namespace SpinDec
