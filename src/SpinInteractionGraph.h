#ifndef SPININTERACTIONGRAPH_H_
#define SPININTERACTIONGRAPH_H_

// SpinInteractionGraph
//
// Spin interaction graph from which spin Hamiltonians are built.
//
// Seto Balian, Jan 27, 2014

#include <utility>
#include <map>
#include <vector>

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
  
  // Edges
  std::map< std::pair<unsigned int, unsigned int>, SpinInteraction*> edges_;

  void check_vertex_label(const unsigned int label) const;

public:

  SpinInteractionGraph();
  
  void add_vertex(const Spin & spin,
                  const SpinState & state,
                  const Eigen::Vector3d & position);

  void add_edge(const unsigned int label1,
                const unsigned int label2,
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

};

#endif // SPININTERACTIONGRAPH_H_
