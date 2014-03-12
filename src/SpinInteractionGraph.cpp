// See SpinInteractionGraph.h for description.
// Seto Balian, Mar 12, 2014

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

SpinInteractionGraph::SpinInteractionGraph()
{ // TODO Is this OK with std::vector initialization?
}

void SpinInteractionGraph::add_vertex(const Spin& spin)
{
  vertices_.push_back(SpinInteractionVertex(num_vertices(),spin));
  basis_ = basis_^spin.get_state().get_basis();
  return;
}

void  SpinInteractionGraph::add_edge(unsigned int label1,
    unsigned int label2, const std::auto_ptr<SpinInteraction>& interaction)
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
      SpinInteractionEdge(get_vertex(label1),get_vertex(label2),
          interaction->clone()));
  return;
}

void  SpinInteractionGraph::set_spin(const unsigned int label,
                                     const Spin& spin)
{
  set_vertex( label, SpinInteractionVertex(label,spin));
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

const Spin&  SpinInteractionGraph::get_spin(
    const unsigned int label) const
{
  return get_vertex(label).get_spin();
}

std::auto_ptr<SpinInteraction> SpinInteractionGraph::get_interaction(
    const unsigned int index) const
{
  return get_edge(index).get_interaction()->clone();
}

SpinVector SpinInteractionGraph::get_spins() const
{
  SpinVector spins;
  for (unsigned int i=0; i<num_vertices();i++) {
    spins.push_back(get_vertex(i).get_spin());
  }
  return spins;
}

SpinBasis  SpinInteractionGraph::build_basis() const
{
  // Start with basis of first spin
  SpinBasis basis = get_spin(0).get_state().get_basis();
  // Loop over vertices combining bases from the rest of the vertices
  for (unsigned int i = 1; i<num_vertices();i++) {
        basis = basis^get_spin(i).get_state().get_basis();// like tensor product
  }
  return basis;
}

void SpinInteractionGraph::join_in_place(const SpinInteractionGraph& to_join)
{
  // Add vertices
  for (unsigned int i=0;i<to_join.num_vertices();i++) {
    add_vertex(to_join.get_vertex(i).get_spin());
  }
  // Add edges
  for (unsigned int i=0;i<to_join.num_edges();i++) {
    add_edge(to_join.get_edge(i).get_vertex1().get_label() + num_vertices(),
             to_join.get_edge(i).get_vertex2().get_label() + num_vertices(),
             to_join.get_interaction(i));
  }
  return;
}

void SpinInteractionGraph::join_in_place(const SpinInteractionGraph& to_join,
    const std::vector<SpinInteractionEdge>& edges)
{
  join(to_join);
  for (unsigned int i=0;i<edges.size();i++) {
    add_edge( edges[i].get_vertex1().get_label(),
              edges[i].get_vertex2().get_label(),
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

SpinInteractionGraph::~SpinInteractionGraph()
{/**/}

} // namespace SpinDec
