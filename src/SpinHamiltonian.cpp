// See SpinHamiltonian.h for description.
// Seto Balian, Jan 31, 2014

#include "SpinHamiltonian.h"
#include "BoostEigen.h"

#include <map>

#include <complex>

// build a combined (like tensor product) SpinBasis
SpinBasis SpinHamiltonian::build_basis(const SpinInteractionGraph& graph) const
{
  SpinBasis basis = graph.get_state(0).get_basis();
  for (unsigned int i = 1; i<graph.num_vertices();i++) {
    basis = basis^graph.get_state(i).get_basis();
  }
  return basis;
}

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
    interaction_ptr->calculate(
        graph.get_position(graph.get_interaction_labels(i).first  ) ,
        graph.get_position(graph.get_interaction_labels(i).second ) );
    interaction_ptr->fill(&matrix_,graph.get_spins(),
        get_basis(),
        graph.get_interaction_labels(i).first,
        graph.get_interaction_labels(i).second);
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
    SpinOperator(build_basis(graph)),
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
