#ifndef SPININTERACTIONNODE_H
#define SPININTERACTIONNODE_H

// SpinInteractionNode
//
// Holds a spin object (to be part of a spin interaction graph) and its
// quantum state.
//
// Seto Balian 21/11/2013

#include "Spin.h"

#include <Eigen/Dense>

class SpinInteractionNode
{

private:
  Spin spin_;
  Eigen::VectorXcd state_;
  bool is_empty_;
  unsigned int label_;

public:
  
  SpinInteractionNode();
  SpinInteractionNode(const Spin & spin, const Eigen::VectorXcd & state,
                                          const unsigned int label);

  Spin get_spin() const;
  Eigen::VectorXcd get_state() const;
  unsigned int get_label() const;
  
  void set_spin(const Spin & spin);
  void set_state(const Eigen::VectorXcd & state);
  void set_label(const unsigned int label);

  bool is_empty() const;

};

#endif // SPININTERACTIONNODE_H

