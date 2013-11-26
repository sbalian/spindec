#ifndef SPININTERACTION_H
#define	SPININTERACTION_H

// SpinInteraction
//
// Base class for interactions between two spins.
// Holds the strength of interaction.
//
// Seto Balian, November 26, 2013

#include <string>
#include "Named.h"

class SpinInteraction : public Named
{

private:
  double strength_; // in M rad s-1

public:
  SpinInteraction();
  SpinInteraction(const double strength);
  
  double get_strength() const;  
  void set_strength(const double strength);
  
  //virtual void calculate() = 0;

};

#endif	 // SPININTERACTION_H
