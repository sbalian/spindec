// See SpinHamiltonian.h for description.
// Seto Balian, Apr 17, 2015

#include "SpinDec/SpinHamiltonian.h"
#include "SpinDec/BoostEigen.h"
#include "SpinDec/Errors.h"

#include <memory>

#include <complex>

namespace SpinDec
{

void SpinHamiltonian::init_terms()
{
  
  for (UInt j=0;j<graph_.num_vertices();j++) {
    zeeman_terms_.push_back(
        ComplexMatrix::Zero(get_dimension(),get_dimension()));
  }
  
  for (UInt j=0;j<graph_.num_edges();j++) {
    interaction_terms_.push_back(
        ComplexMatrix::Zero(get_dimension(),get_dimension()));
  }
  
  return;
}

void SpinHamiltonian::sum_zeeman_terms()
{
  zeeman_hamiltonian_ = ComplexMatrix(get_dimension(),get_dimension());
  zeeman_hamiltonian_.setZero();
  
  for (UInt i=0;i<graph_.num_vertices();i++) {
    zeeman_hamiltonian_ += zeeman_terms_[i];
  }
  
  return;
}

void SpinHamiltonian::sum_interaction_terms()
{
  interaction_hamiltonian_ = ComplexMatrix(get_dimension(),get_dimension());
  interaction_hamiltonian_.setZero();
  
  for (UInt i=0;i<graph_.num_edges();i++) {
    interaction_hamiltonian_ += interaction_terms_[i];
  }
  
  return;
}


// fill diagonal elements with gyromagnetic_ratio*magnetic_quantum_number*
// field_strength for spin in given vertex
void SpinHamiltonian::fill_zeeman(const UInt vertex_label)
{
  // fill diagonal elements [M rad s-1]
  
  // loop over diagonal elements
  for (unsigned int i=0; i<get_dimension();i++) {
      zeeman_terms_[vertex_label](i,i) = 
          get_basis().get_element(i,vertex_label)*// magnetic quantum number
          get_field().get_magnitude()*// field strength [T]
          graph_.get_spin_parameters(vertex_label).get_gyromagnetic_ratio();
          // gyromagnetic ratio
          // [M rad s-1]
  }
  
  return;
}


// fill elements for spin interaction at given edge
void SpinHamiltonian::fill_interaction(const UInt edge_index)
{
//  cout << "Number of vertices: " << graph_.vertices_.size() << endl;
//  cout << "Number of edges: " << graph_.edges_.size() << endl;
  
//  for (UInt i=0;i<graph_.edges_.size();i++) {
//    cout << graph_.edges_[i].get_label2() << endl;
//  }

  // Loop over edges
    auto_ptr<SpinInteraction> interaction_ptr =
        graph_.get_interaction(edge_index);
    if (!interaction_ptr->strength_preset()) { // calculate only if strength
                                               // NOT preset
      
      interaction_ptr -> calculate(
          
          
          graph_.get_vertex1(edge_index).get_spin_parameters(),
          graph_.get_vertex2(edge_index).get_spin_parameters(),
          graph_.get_vertex1(edge_index).get_position(),
          graph_.get_vertex2(edge_index).get_position(),
                            get_field());
      
      
    }
    
    //graph_.set_interaction(edge_index,interaction_ptr->clone());
    
    interaction_ptr->fill(&interaction_terms_[edge_index],
        graph_.spin_parameters_vector(),
        get_basis(),
        graph_.get_edge(edge_index).get_label1(),
        graph_.get_edge(edge_index).get_label2());
  
  return;
}


// fill diagonal elements with gyromagnetic_ratio*magnetic_quantum_number*
// field_strength for all spins in the graph
void SpinHamiltonian::fill_zeeman()
{
  // loop over vertices
  for (unsigned int j=0;j<graph_.num_vertices();j++) {
    fill_zeeman(j);
  }
  return;
}

// fill elements for all spin interaction
void SpinHamiltonian::fill_interactions()
{
  
  // Loop over edges
  for (unsigned int i=0;i<graph_.num_edges();i++) {
    
    fill_interaction(i);
        
  }
  
  
  
  return;
}


SpinHamiltonian::SpinHamiltonian() : SpinOperator(),
    field_(UniformMagneticField()),graph_(SpinInteractionGraph())
{
}

SpinHamiltonian::SpinHamiltonian(const SpinInteractionGraph& graph,
    const UniformMagneticField & field) :
    SpinOperator(graph.get_basis()),
    field_(field),graph_(graph)
{

  init_terms();  
  fill_zeeman();
  fill_interactions();
  sum_interaction_terms();
  sum_zeeman_terms();
  matrix_ = zeeman_hamiltonian_ + interaction_hamiltonian_;
  
  
  return;
}

UniformMagneticField SpinHamiltonian::get_field() const
{
  return field_;
}

const SpinInteractionGraph& SpinHamiltonian::get_graph() const
{
  return graph_;
}


void SpinHamiltonian::update_positions(const UIntArray& vertex_labels,
    const vector<ThreeVector>& positions)
{
    
  if (vertex_labels.size() != positions.size()) {
    Errors::quit("Vertex label and position arrays must be of the same size.");
    return;
  }
  
  // set the new positions
  for (UInt l=0;l<vertex_labels.size();l++) {
    graph_.set_position(vertex_labels[l],positions[l]);
  }
  
  // TODO filling unchanged interactions as well ...
  interaction_hamiltonian_.setZero();
  for (UInt i=0;i<interaction_terms_.size();i++) {
    interaction_terms_[i].setZero();
  }
  fill_interactions();
  
// TODO buggy
//  for (UInt i=0;i<graph_.num_edges();i++) {
//    
//    bool to_change = false;
//    for (UInt j=0;j<vertex_labels.size();j++) {
//      if (graph_.get_edge(i).get_label1() == vertex_labels[j]) {
//        to_change = true;
//        break;
//      }
//      if (graph_.get_edge(i).get_label2() == vertex_labels[j]) {
//        to_change = true;
//        break;
//      }
//    }
//    
//    if (to_change == true) {
//      fill_interaction(i);
//    }
//    
//  }
  
  // resum
  sum_interaction_terms();
  // reset matrix
  matrix_ = zeeman_hamiltonian_ + interaction_hamiltonian_;
  
  return;
  
}

}// namespace SpinDec

