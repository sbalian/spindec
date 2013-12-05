#ifndef SPININTERACTIONVERTEX_H_
#define SPININTERACTIONVERTEX_H_

// SpinInteractionVertex
//
// Vertex for a spin interaction graph.
// Holds a label, a spin object, the quantum state of a spin and its spatial
// position in Angstroms.
//
// Seto Balian, Dec 5, 2013

#include <Eigen/Dense>

#include "Spin.h"
#include "SpinState.h"

class SpinInteractionVertex
{

private:
  unsigned int label_;
  Spin spin_;
  SpinState state_;
  Eigen::Vector3d position_;

public:
  
  SpinInteractionVertex();
  SpinInteractionVertex(const unsigned int label,
      const Spin & spin, const SpinState & state,
      const Eigen::Vector3d & position);
  
  unsigned int get_label() const;
  Spin get_spin() const;
  SpinState get_state() const;
  Eigen::Vector3d get_position() const;
  
  void set_label(const unsigned int label);
  void set_spin(const Spin & spin);
  void set_state(const SpinState & state);
  void set_position(const Eigen::Vector3d & position);
  
};

#endif // SPININTERACTIONVERTEX_H_
