#ifndef SPININTERACTIONGRAPH_H_
#define SPININTERACTIONGRAPH_H_

// SpinInteractionGraph
//
// Spin interaction graph from which spin Hamiltonians are built.
//
// Seto Balian, Dec 10, 2013

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

  std::vector<SpinInteraction*> interactions_; // TODO is cleanup required?

public:

  SpinInteractionGraph();
  

  // void set_position(const Eigen::Vector3d & position);


};

#endif // SPININTERACTIONGRAPH_H_
