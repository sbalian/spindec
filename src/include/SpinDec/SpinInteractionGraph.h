#ifndef SPININTERACTIONGRAPH_H_
#define SPININTERACTIONGRAPH_H_

// SpinDec::SpinInteractionGraph
//
// Spin interaction graph from which spin Hamiltonians are built.
//
// Seto Balian, May 28, 2014

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinInteractionVertex.h"
#include "SpinDec/SpinInteractionEdge.h"

#include "SpinDec/SpinParametersVector.h"

#include "SpinDec/SpinBasis.h"

namespace SpinDec
{

class SpinInteractionGraph
{
  
private:
  
  // Vertices
  vector<SpinInteractionVertex> vertices_;
  // Edges
  vector<SpinInteractionEdge> edges_;
  
  SpinBasis basis_;
  
  void quit_if_vertex_label_out_of_bounds(const unsigned int label) const;
  void quit_if_edge_index_out_of_bounds(const unsigned int index) const;
  
  void set_vertex(const unsigned int label,const SpinInteractionVertex& vertex);
  void set_edge(const unsigned int index,const SpinInteractionEdge& edge);
  
  
public:

  SpinInteractionGraph();
  
  void set_basis(const SpinBasis & basis);
  
  // these vertex add methods combine the new basis to basis_
  // (like tensor product)
  void add_vertex(const SpinParameters& spin_parameters,
                  const ThreeVector & position); // basis built from spin
                                                 // parameters
  void add_vertex(const SpinParameters& spin_parameters,
                  const SpinBasis& basis,
                  const ThreeVector & position);
  
  // these vertex add methods append the new basis to basis_
  void add_vertex_appending_basis(const SpinParameters& spin_parameters,
      const ThreeVector & position);
  
  void add_vertex_appending_basis(const SpinParameters& spin_parameters,
                  const SpinBasis& basis,
                  const ThreeVector & position);

  void add_edge(unsigned int label1,
                unsigned int label2,
                const std::auto_ptr<SpinInteraction>& interaction);
    
  unsigned int num_vertices() const;
  unsigned int num_edges() const;
  void clear();
  
  const SpinBasis& get_basis() const;
  
  const SpinParameters& get_spin_parameters(const unsigned int label) const;
  const ThreeVector& get_position(const unsigned int label) const;

  std::auto_ptr<SpinInteraction> get_interaction(const unsigned int index)const;
  
  SpinParametersVector spin_parameters_vector() const;
  
  const SpinInteractionVertex& get_vertex(const unsigned int label) const;
  const SpinInteractionEdge& get_edge(const unsigned int index) const;
  
  // Adds input graph to current graph, preserving all vertices and edges.
  // Vertex labels of given graph 0,1,2 ... become n, n+1, n+2
  // where n is the number of vertices of the original graph.
  // There are no edges connecting the two graphs.
  // Uses the add_vertex method (combining bases).
  void join_in_place(const SpinInteractionGraph & to_join);
  // Same as above, but with edges connecting the two graphs.
  // Edges should be valid for the graph after joining!
  void join_in_place(const SpinInteractionGraph & to_join,
            const std::vector<SpinInteractionEdge> & edges);
  // Same as above but the original graph remains unchanged and output is a new
  // graph
  SpinInteractionGraph join(const SpinInteractionGraph & to_join) const;
  SpinInteractionGraph join(const SpinInteractionGraph & to_join,
            const std::vector<SpinInteractionEdge> & edges) const;
    
};

} // namespace SpinDec

#endif // SPININTERACTIONGRAPH_H_
