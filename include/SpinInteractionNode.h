#ifndef SPININTERACTIONNODE_H
#define SPININTERACTIONNODE_H

// SpinInteractionNode
//
// Holds a spin object (to be part of a spin interaction graph) and it's
// quantum state.
//
// Seto Balian 19/11/2013

#include "Spin.h"

#include <Eigen/Dense>

class SpinInteractionNode
{

private:
  Spin spin_;
  Eigen::VectorXcd state_;
  bool is_empty_;
  int label_;

public:
  
  SpinInteractionNode();
  SpinInteractionNode(const Spin & spin, const Eigen::VectorXcd & state,
                                          const int label);

  Spin get_spin() const;
  Eigen::VectorXcd get_state() const;
  int get_label() const;
  
  void set_spin(const Spin & spin);
  void set_state(const Eigen::VectorXcd & state);
  void set_label(const int label);

  bool is_empty() const;

};

#endif // SPININTERACTIONNODE_H

