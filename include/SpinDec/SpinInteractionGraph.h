#ifndef SPININTERACTIONGRAPH_H_
#define SPININTERACTIONGRAPH_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinInteractionVertex.h"
#include "SpinDec/SpinInteractionEdge.h"

#include "SpinDec/SpinParametersVector.h"

#include "SpinDec/SpinBasis.h"

namespace SpinDec
{

/// Spin interaction graph from which spin Hamiltonians are built.
class SpinInteractionGraph
{
  
private:
  
  /// Vertices.
  vector<SpinInteractionVertex> vertices_;
  /// Edges.
  vector<SpinInteractionEdge> edges_;
  
  SpinBasis basis_;
  
  void quit_if_vertex_label_out_of_bounds(const unsigned int label) const;
  void quit_if_edge_index_out_of_bounds(const unsigned int index) const;
  
  void set_vertex(const unsigned int label,const SpinInteractionVertex& vertex);
  void set_edge(const unsigned int index,const SpinInteractionEdge& edge);
  
  
public:

  SpinInteractionGraph();
  
  void set_basis(const SpinBasis & basis);
  
  /**
   * This vertex add method combines the new basis to basis_
   * (like tensor product).
   * Basis built from spin parameters.
   */
  void add_vertex(const SpinParameters& spin_parameters,
                  const ThreeVector & position); 
  
  /**
   * This vertex add method combines the new basis to basis_
   * (like tensor product).
   */
  void add_vertex(const SpinParameters& spin_parameters,
                  const SpinBasis& basis,
                  const ThreeVector & position);
  
  /// This vertex add method appends the new basis to basis_.
  void add_vertex_appending_basis(const SpinParameters& spin_parameters,
      const ThreeVector & position);
  
  /// This vertex add method appends the new basis to basis_.
  void add_vertex_appending_basis(const SpinParameters& spin_parameters,
                  const SpinBasis& basis,
                  const ThreeVector & position);

  void add_edge(unsigned int label1,
                unsigned int label2,
                const shared_ptr<SpinInteraction>& interaction);
  
  void add_edges(const vector<SpinInteractionEdge>& edges);
  
  unsigned int num_vertices() const;
  unsigned int num_edges() const;
  void clear();
  
  const SpinBasis& get_basis() const;
  
  const SpinParameters& get_spin_parameters(const unsigned int label) const;
  const ThreeVector& get_position(const unsigned int label) const;

  shared_ptr<SpinInteraction> get_interaction(const unsigned int index)const;
  void set_interaction(const unsigned int index,
      const shared_ptr<SpinInteraction>& interaction );
  
  SpinParametersVector spin_parameters_vector() const;
  
  const SpinInteractionVertex& get_vertex(const unsigned int label) const;
  const SpinInteractionEdge& get_edge(const unsigned int index) const;
  
  /**
   * Adds input graph to current graph, preserving all vertices and edges.
   * Vertex labels of given graph \f$0,1,2,\dots\f$ become
   * \f$n, n+1, n+2, \dots\f$,
   * where \f$n\f$ is the number of vertices of the original graph.
   * There are no edges connecting the two graphs.
   * Uses the add_vertex method (combining bases).
   */
  void join_in_place(const SpinInteractionGraph & to_join);
  
  /**
   * Same as join_in_place(const SpinInteractionGraph &),
   * but with edges connecting the two graphs.
   * Edges should be valid for the graph after joining!
   */  
  void join_in_place(const SpinInteractionGraph & to_join,
            const std::vector<SpinInteractionEdge> & edges);
  
  /**
   * Like  join_in_place(const SpinInteractionGraph &) but the original
   * graph remains unchanged and output is a new graph.
   */
  SpinInteractionGraph join(const SpinInteractionGraph & to_join) const;
  
  /**
   * Like 
   * join_in_place(const SpinInteractionGraph &,
   * const std::vector<SpinInteractionEdge> &) but the original
   * graph remains unchanged and output is a new graph.
   */
  SpinInteractionGraph join(const SpinInteractionGraph & to_join,
            const std::vector<SpinInteractionEdge> & edges) const;
  
  void set_position(const UInt label,const ThreeVector& position);
  
  const SpinInteractionVertex& get_vertex1(const UInt index) const;
                                                              // edge index
  const SpinInteractionVertex& get_vertex2(const UInt index) const;
                                                              // edge index
  
  void set_positions(const UIntArray& vertex_labels,
      const vector<ThreeVector>& positions);
    
};

} // namespace SpinDec

#endif // SPININTERACTIONGRAPH_H_
