#ifndef SPININTERACTIONNODE_H
#define SPININTERACTIONNODE_H

// SpinInteractionNode
//
// Holds a spin object (to be part of a spin interaction graph).
//
// Seto Balian 22/10/2013

#include "Spin.h"

class SpinInteractionNode
{

private:
  Spin spin_;
  bool is_empty_;
  int label_;

public:
  
  SpinInteractionNode();
  SpinInteractionNode(const Spin & spin, const int label);

  Spin get_spin() const;
  int get_label() const;
  void set_spin(const Spin & spin);
  void set_label(const int label);

  bool is_empty() const;

};

#endif // SPININTERACTIONNODE_H

