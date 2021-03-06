// See SpinInteractionGraph.h for description.
// Seto Balian, Apr 17, 2015

#include "SpinDec/SpinInteractionGraph.h"
#include "SpinDec/Errors.h"

#include <algorithm>

namespace SpinDec
{

void SpinInteractionGraph::quit_if_vertex_label_out_of_bounds(
    const unsigned int label) const
{
  
  if (label >= num_vertices()) {
    Errors::quit("Vertex label out of bounds.");
  }
  return;
}

void SpinInteractionGraph::quit_if_edge_index_out_of_bounds(
    const unsigned int index) const
{
  if (index >= num_edges()) {
    Errors::quit("Edge index out of bounds.");
  }
  return;
}

void SpinInteractionGraph::set_vertex(const unsigned int label,
    const SpinInteractionVertex& vertex)
{
  quit_if_vertex_label_out_of_bounds(label);
  vertices_[label] = vertex;
  return;
}

void SpinInteractionGraph::set_edge(const unsigned int index,
    const SpinInteractionEdge& edge)
{
  quit_if_edge_index_out_of_bounds(index);
  edges_[index] = edge;
  return;
}

void SpinInteractionGraph::set_basis(const SpinBasis & basis)
{
  basis_ = basis;
  return;
}

SpinInteractionGraph::SpinInteractionGraph() : basis_(SpinBasis())
{ // TODO Is this OK with std::vector initialization?
}

void SpinInteractionGraph::add_vertex(const SpinParameters& spin_parameters,
                const ThreeVector & position)
{
  SpinInteractionVertex vertex(SpinInteractionVertex(num_vertices(),
      spin_parameters,position));
  vertices_.push_back(vertex);
  if (num_vertices() == 1) {
    basis_ = vertex.get_basis();
  } else {
      basis_ = basis_^vertex.get_basis();
  }
  return;
}

void SpinInteractionGraph::add_vertex(const SpinParameters& spin_parameters,
                const SpinBasis& basis,
                const ThreeVector & position)
{
  SpinInteractionVertex vertex(SpinInteractionVertex(num_vertices(),
      spin_parameters,basis,position));
  vertices_.push_back(vertex);
  if (num_vertices() == 1) {
    basis_ = vertex.get_basis();
  } else {
      basis_ = basis_^vertex.get_basis();
  }
  return;
}

void SpinInteractionGraph::add_vertex_appending_basis(
    const SpinParameters& spin_parameters,
    const ThreeVector & position)
{
  SpinInteractionVertex vertex(SpinInteractionVertex(num_vertices(),
      spin_parameters,position));
  vertices_.push_back(vertex);
  if (num_vertices() == 1) {
    basis_ = vertex.get_basis();
  } else {
      basis_ = basis_+vertex.get_basis();
  }
  return;
}

void SpinInteractionGraph::add_vertex_appending_basis(
    const SpinParameters& spin_parameters,
                const SpinBasis& basis,
                const ThreeVector & position)
{
  SpinInteractionVertex vertex(SpinInteractionVertex(num_vertices(),
      spin_parameters,basis,position));
  vertices_.push_back(vertex);
  if (num_vertices() == 1) {
    basis_ = vertex.get_basis();
  } else {
      basis_ = basis_+vertex.get_basis();
  }
  return;
}

void  SpinInteractionGraph::add_edge(unsigned int label1,
    unsigned int label2, const shared_ptr<SpinInteraction>& interaction)
{
  
  // First make sure label1 != label2
  if (label1 == label2) {
    Errors::quit("Labels must be different when adding an edge!");
    return;
  }
  // Now make sure label1 < label2 and swap if not the case
  if (label1 > label2) {
    std::swap(label1,label2);
  }
      
  edges_.push_back(
      SpinInteractionEdge(label1,label2,
          interaction->clone()));

  return;
}

unsigned int SpinInteractionGraph::num_vertices() const
{
  return vertices_.size();
}

unsigned int SpinInteractionGraph::num_edges() const
{
  return edges_.size();
}

void  SpinInteractionGraph::clear()
{
  vertices_.clear();
  edges_.clear();
  return;
}

const SpinParameters&  SpinInteractionGraph::get_spin_parameters(
    const unsigned int label) const
{
  return get_vertex(label).get_spin_parameters();
}

const SpinBasis& SpinInteractionGraph::get_basis() const
{
  return basis_;
}

const ThreeVector& SpinInteractionGraph::get_position(const UInt label) const
{
  return get_vertex(label).get_position();
}

shared_ptr<SpinInteraction> SpinInteractionGraph::get_interaction(
    const unsigned int index) const
{
  return get_edge(index).get_interaction()->clone();
}

void SpinInteractionGraph::set_interaction(const unsigned int index,
    const shared_ptr<SpinInteraction>& interaction )
{
  edges_[index] =
      SpinInteractionEdge(edges_[index].get_label1(),
                          edges_[index].get_label2(),interaction->clone());
  return;
}


SpinParametersVector SpinInteractionGraph::spin_parameters_vector() const
{
  SpinParametersVector spin_parameters_vector;
  for (unsigned int i=0; i<num_vertices();i++) {
    spin_parameters_vector.push_back(get_vertex(i).get_spin_parameters());
  }
  return spin_parameters_vector;
}

const SpinInteractionVertex& SpinInteractionGraph::get_vertex(
    const unsigned int label) const
{
  quit_if_vertex_label_out_of_bounds(label);
  return vertices_[label];
}

const SpinInteractionEdge& SpinInteractionGraph::get_edge(
                                                const unsigned int index) const
{
  quit_if_edge_index_out_of_bounds(index);
  return edges_[index];
}

void SpinInteractionGraph::join_in_place(const SpinInteractionGraph& to_join)
{
  
  const UInt old_num_vertices = num_vertices();
  
  // Add vertices
  for (unsigned int i=0;i<to_join.num_vertices();i++) {
    add_vertex(to_join.get_vertex(i).get_spin_parameters(),
        to_join.get_vertex(i).get_basis(),to_join.get_vertex(i).get_position());
  }
    
  // Add edges
  for (unsigned int i=0;i<to_join.num_edges();i++) {
    add_edge(to_join.get_edge(i).get_label1() + old_num_vertices,
             to_join.get_edge(i).get_label2() + old_num_vertices,
             to_join.get_interaction(i));
  }
  return;
}

void SpinInteractionGraph::join_in_place(const SpinInteractionGraph& to_join,
    const std::vector<SpinInteractionEdge>& edges)
{
  join(to_join);
  for (unsigned int i=0;i<edges.size();i++) {
    add_edge( edges[i].get_label1(),
              edges[i].get_label2(),
              edges[i].get_interaction());
  }
  return;
}

SpinInteractionGraph SpinInteractionGraph::join(
    const SpinInteractionGraph & to_join) const
{
  SpinInteractionGraph output = *this;
  output.join_in_place(to_join);
  return output;
}

SpinInteractionGraph SpinInteractionGraph::join(
    const SpinInteractionGraph & to_join,
    const std::vector<SpinInteractionEdge> & edges) const
{
  SpinInteractionGraph output = *this;
  output.join_in_place(to_join,edges);
  return output;
}

void SpinInteractionGraph::set_position(const UInt label,
    const ThreeVector& position)
{
  quit_if_vertex_label_out_of_bounds(label);
  vertices_[label].set_position(position);
  return;
}

const SpinInteractionVertex& SpinInteractionGraph::get_vertex1(
    const UInt index) const
{
  quit_if_edge_index_out_of_bounds(index);
  return  get_vertex( get_edge(index).get_label1() );
}

const SpinInteractionVertex& SpinInteractionGraph::get_vertex2(
    const UInt index) const
{
  quit_if_edge_index_out_of_bounds(index);
  return  get_vertex( get_edge(index).get_label2() );
}

void SpinInteractionGraph::add_edges(
    const vector<SpinInteractionEdge>& edges)
{
  
  for (UInt i=0;i<edges.size();i++) {
    add_edge( edges[i].get_label1(),edges[i].get_label2(),
        edges[i].get_interaction());
  }
  
  return;
}

void SpinInteractionGraph::set_positions(
    const UIntArray& vertex_labels, const vector<ThreeVector>& positions)
{
  
  if (vertex_labels.size() != positions.size()) {
    Errors::quit("Vertex label and position arrays must be of the same size.");
    return;
  }
  
  for (UInt i=0;i<vertex_labels.size();i++) {
    set_position(vertex_labels[i],positions[i]);
  }
  
  return;
  

}



} // namespace SpinDec

