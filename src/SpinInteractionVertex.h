#ifndef SPININTERACTIONVERTEX_H_
#define SPININTERACTIONVERTEX_H_

// SpinInteractionVertex
//
// TODO Describe
//
// Seto Balian, Dec 3, 2013

class SpinInteractionVertex
{

private:
  unsigned int label_; // TODO const data member, but problems with std vector

public:
  
  SpinInteractionVertex(); // label set to zero
  SpinInteractionVertex(const unsigned int label); // label set to zero
  
  unsigned int get_label() const;
  
};

#endif // SPININTERACTIONVERTEX_H_
