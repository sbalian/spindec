#ifndef SPININTERACTIONVERTEX_H
#define SPININTERACTIONVERTEX_H

// SpinInteractionVertex
//
// @todo Describe
//
// Seto Balian, December 2, 2013

class SpinInteractionVertex
{

private:
  unsigned int label_; // @todo const data member, but problems with std vector

public:
  
  SpinInteractionVertex(); // label set to zero
  SpinInteractionVertex(const unsigned int label); // label set to zero
  
  unsigned int get_label() const;
  
};

#endif // SPININTERACTIONVERTEX_H
