#ifndef SPININTERACTIONVERTEXCONTENTS_H_
#define SPININTERACTIONVERTEXCONTENTS_H_

// SpinInteractionVertexContents
//
// Vertex contents for a spin interaction graph.
//
// Seto Balian, Dec 13, 2013

#include "VertexContents.h"

#include "Spin.h"
#include "SpinState.h"

#include <Eigen/Dense>

class SpinInteractionVertexContents : public VertexContents
{
private:
  Spin spin_;
  SpinState state_;
  Eigen::Vector3d position_; // in Angstroms
  
public:
  
  SpinInteractionVertexContents();
  SpinInteractionVertexContents(const Spin & spin,
      const SpinState & state,
      const Eigen::Vector3d & position);
  
  Spin get_spin() const;
  SpinState get_state() const;
  Eigen::Vector3d get_position() const;
  
  void set_position(const Eigen::Vector3d & position);
  
};

#endif // SPININTERACTIONVERTEXCONTENTS_H_
