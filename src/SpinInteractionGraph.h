#ifndef SPININTERACTIONGRAPH_H_
#define SPININTERACTIONGRAPH_H_

// SpinInteractionGraph
//
// Spin interaction graph from which spin Hamiltonians are built.
//
// Seto Balian, Mar 3, 2014

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
  virtual SpinBasis build_basis() const;

  // Adds input graph to current graph, preserving all vertices and edges.
  // Vertex labels of given graph 0,1,2 ... become n, n+1, n+2
  // where n is the number of vertices of the original graph.
  // There are no edges connecting the two graphs.
  void join(const SpinInteractionGraph & to_join);
  // Same as above, but with edges connecting the two graphs.
  // Edges should be valid for the graph after joining!
  void join(const SpinInteractionGraph & to_join,
            const std::vector<SpinInteractionEdge> & edges);
  
  virtual ~SpinInteractionGraph();
  
};

} // namespace SpinDecoherence

#endif // SPININTERACTIONGRAPH_H_
