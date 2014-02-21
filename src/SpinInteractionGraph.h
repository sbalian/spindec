#ifndef SPININTERACTIONGRAPH_H_
#define SPININTERACTIONGRAPH_H_

// SpinInteractionGraph
//
// Spin interaction graph from which spin Hamiltonians are built.
//
// Seto Balian, Feb 21, 2014

#include "SpinInteractionVertex.h"
#include "SpinInteractionEdge.h"

#include "SpinVector.h"

#include <vector>

namespace SpinDecoherence
{

class SpinInteractionGraph
{
  
private:
  
  // Vertices
  std::vector<SpinInteractionVertex> vertices_;
  // Edges
  std::vector<SpinInteractionEdge> edges_;
  
  void quit_if_vertex_label_out_of_bounds(const unsigned int label) const;
  void quit_if_edge_index_out_of_bounds(const unsigned int index) const;
  
  void set_vertex(const unsigned int label,const SpinInteractionVertex& vertex);
  void set_edge(const unsigned int index,const SpinInteractionEdge& edge);
  
public:

  SpinInteractionGraph();
  
  void add_vertex(const Spin & spin);
  void add_edge(unsigned int label1,
                unsigned int label2,
                SpinInteraction* interaction);
  
  void set_spin(const unsigned int label,const Spin& spin);
  
  unsigned int num_vertices() const;
  unsigned int num_edges() const;
  void clear();
  
  const Spin& get_spin(const unsigned int label) const;
  SpinInteraction* get_interaction(const unsigned int index) const;
  
  SpinVector get_spins() const;
  
  const SpinInteractionVertex& get_vertex(const unsigned int label) const;
  const SpinInteractionEdge& get_edge(const unsigned int index) const;

    
  // build a combined (like tensor product) SpinBasis and return it
  SpinBasis build_basis() const;

  void join(const SpinInteractionGraph & to_join);
  
};

} // namespace SpinDecoherence

#endif // SPININTERACTIONGRAPH_H_
