#ifndef SPININTERACTIONNODE_H
#define SPININTERACTIONNODE_H

// SpinInteractionNode
//
// Holds: Spin, vector position in real space [Angstroms], spin quantum state
//
//(to be part of a spin interaction graph) and its
// quantum state.
//
// Seto Balian, November 27, 2013

#include "Spin.h"

#include <Eigen/Dense>

class SpinInteractionNode
{

private:
  Spin spin_;
  bool is_empty_;
  unsigned int label_;
  
  void quit_if_empty(const SpinInteractionNode & node) const;


public:
  
  SpinInteractionNode();
  SpinInteractionNode(const Spin & spin, const unsigned int label);

  Spin get_spin() const;
  unsigned int get_label() const;
  
  void set_spin(const Spin & spin);
  void set_label(const unsigned int label);

  bool is_empty() const;

};

#endif // SPININTERACTIONNODE_H

