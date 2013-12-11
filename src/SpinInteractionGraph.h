#ifndef SPININTERACTIONGRAPH_H_
#define SPININTERACTIONGRAPH_H_

// SpinInteractionGraph
//
// Spin interaction graph from which spin Hamiltonians are built.
//
// Seto Balian, Dec 11, 2013

#include "LabeledGraph.h"

#include "Spin.h"
#include "SpinState.h"
#include "SpinInteraction.h"

#include <Eigen/Dense>

#include <vector>

class SpinInteractionGraph : LabeledGraph
{

private:

  std::vector<Spin> spins_;
  std::vector<SpinState> states_;
  std::vector<Eigen::Vector3d> positions_;

  std::vector<unsigned int> vertex_label_map_;

  std::vector<SpinInteraction*> interactions_; // TODO is cleanup required?

public:

  SpinInteractionGraph();
  
  virtual void add_vertex(const LabeledVertex & vertex);
  virtual void add_edge(const Edge & edge);

  void add_vertex(const LabeledVertex & vertex, const Spin & spin,
      const SpinState & state, const Eigen::Vector3d & position);
  void add_edge(const Edge & edge, const SpinInteraction* interaction);

  Spin get_spin(const unsigned int vertex_label) const;
  SpinState get_state(const unsigned int vertex_label) const;
  Eigen::Vector3d get_position(const unsigned int vertex_label) const;
  SpinInteraction* get_interaction(const unsigned int vertex_label1,
                                   const unsigned int vertex_label2) const;

  void set_position(const unsigned int vertex_label,
      const Eigen::Vector3d & position);

};

#endif // SPININTERACTIONGRAPH_H_
