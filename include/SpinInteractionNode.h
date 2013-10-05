#ifndef SPININTERACTIONNODE_H
#define SPININTERACTIONNODE_H

// Spin interaction node
//
// TODO Describe
//
// Seto Balian 04/10/2013

#include "Spin.h"

class SpinInteractionNode
{

private:
  Spin spin_;

  bool isEmpty_;

public:
  
  SpinInteractionNode();
  SpinInteractionNode(const Spin & spin);

  Spin get_spin() const;
  void set_spin(const Spin & spin);


  bool isEmpty() const;

};


#endif // SPININTERACTIONNODE_H

