#ifndef SPININTERACTIONVERTEX_H
#define SPININTERACTIONVERTEX_H

// SpinInteractionVertex
//
// Interaction between a pair of nodes each containing one Spin.
// Holds the labels for the two interacting spins as well as a SpinInteraction
// object.
//
// @todo Add more description ...
//
// Seto Balian, November 27, 2013

#include <utility>
#include <string>

#include "SpinInteraction.h"

#include <string>

class SpinInteractionVertex
{

private:
  std::pair<unsigned int,unsigned int> labels_;
  SpinInteraction interaction_; // see SpinInteraction.h and derived classes
  
  void set_interaction(const SpinInteraction & interaction);
  
public:

  SpinInteractionVertex();
  SpinInteractionVertex(const unsigned int label1,
                        const unsigned int label2,
                        const SpinInteraction & interaction);

  unsigned int get_label1() const;
  unsigned int get_label2() const;
  // uses Named::class
  std::string get_interaction_type() const;

  void set_labels(const unsigned int label1,
                  const unsigned int label2);

  void set_label1(const unsigned int label);
  void set_label2(const unsigned int label);
  
};

#endif // SPININTERACTIONVERTEX_H
