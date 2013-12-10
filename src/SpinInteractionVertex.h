#ifndef SPININTERACTIONVERTEX_H_
#define SPININTERACTIONVERTEX_H_

// SpinInteractionVertex
//
// Vertex for a spin interaction graph.
// Holds a spin object, the quantum state of a spin and its spatial
// position in Angstroms.
//
// Seto Balian, Dec 10, 2013

#include <Eigen/Dense>

#include "Spin.h"
#include "SpinState.h"
#include "LabeledVertex.h"

class SpinInteractionVertex : public LabeledVertex
{

private:
  Spin spin_;
  SpinState state_;
  Eigen::Vector3d position_;

public:
  
  SpinInteractionVertex();
  SpinInteractionVertex(const unsigned int label,
      const Spin & spin, const SpinState & state,
      const Eigen::Vector3d & position);
  
  Spin get_spin() const;
  SpinState get_state() const;
  Eigen::Vector3d get_position() const;
  
  void set_position(const Eigen::Vector3d & position);
  
};

#endif // SPININTERACTIONVERTEX_H_
