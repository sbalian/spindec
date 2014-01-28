#ifndef SPININTERACTIONGRAPH_H_
#define SPININTERACTIONGRAPH_H_

// SpinInteractionGraph
//
// Spin interaction graph from which spin Hamiltonians are built.
//
// Seto Balian, Jan 28, 2014

#include <vector>
#include <utility>

#include "SpinInteraction.h"
#include "SpinVector.h"
#include "SpinState.h"

#include <Eigen/Dense>

class SpinInteractionGraph
{
  
private:
  
  // Vertices
  // indices are labels for vertex used in map below
  SpinVector spins_;
  std::vector<SpinState> states_;
  std::vector<Eigen::Vector3d> positions_; // Spatial positions in Angstroms
  
  unsigned int num_vertices_;
  unsigned int num_edges_;
  
  // Edges
  std::vector<unsigned int> vertex_labels1_, vertex_labels2_;
  std::vector<SpinInteraction*> interactions_;
  
  void check_vertex_label(const unsigned int label) const;
  void check_edge_index(const unsigned int index) const;


public:

  SpinInteractionGraph();
  
  void add_vertex(const Spin & spin,
                  const SpinState & state,
                  const Eigen::Vector3d & position);

  void add_edge(unsigned int label1,
                unsigned int label2,
                SpinInteraction* interaction);
  
  void set_spin(const unsigned int label,const Spin & spin);
  void set_position(const unsigned int label, const Eigen::Vector3d position);
  void set_state(const unsigned int label, const SpinState & state);
  
  unsigned int num_vertices() const;
  unsigned int num_edges() const;
  void clear();
  
  Spin get_spin(const unsigned int label) const;  
  SpinState get_state(const unsigned int label) const;
  Eigen::Vector3d get_position(const unsigned int label) const;
  
  SpinInteraction* get_interaction(const unsigned int index) const;
  std::pair<unsigned int,unsigned int> get_interaction_labels(
      const unsigned int index) const;
  
  SpinVector get_spins() const;

  void join(const SpinInteractionGraph & to_join);
  
};

#endif // SPININTERACTIONGRAPH_H_
