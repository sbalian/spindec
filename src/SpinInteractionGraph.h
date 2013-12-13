#ifndef SPININTERACTIONGRAPH_H_
#define SPININTERACTIONGRAPH_H_

// SpinInteractionGraph
//
// Spin interaction graph from which spin Hamiltonians are built.
//
// Seto Balian, Dec 13, 2013

#include "LabeledGraph.h"
#include "LabeledVertex.h"
#include "Edge.h"

#include "SpinInteractionVertexContents.h"
#include "SpinInteractionEdgeContents.h"

class SpinInteractionGraph : LabeledGraph
{

public:

  SpinInteractionGraph();
  
  void add_vertex(const LabeledVertex & vertex,
                  const SpinInteractionVertexContents & contents);
  void add_edge(const Edge & edge,
                  const SpinInteractionEdgeContents & contents);

//  void add_vertex(const LabeledVertex & vertex,
//                  const Spin & spin,
//      const SpinState & state, const Eigen::Vector3d & position);
//  void add_edge(const Edge & edge, SpinInteraction* interaction);
//
//  Spin get_spin(const unsigned int vertex_label) const;
//  SpinState get_state(const unsigned int vertex_label) const;
//  Eigen::Vector3d get_position(const unsigned int vertex_label) const;
//  
//  SpinInteraction* get_interaction(const unsigned int vertex_label1,
//                                   const unsigned int vertex_label2) const;
//
//  void set_position(const unsigned int vertex_label,
//      const Eigen::Vector3d & position);

};

#endif // SPININTERACTIONGRAPH_H_
