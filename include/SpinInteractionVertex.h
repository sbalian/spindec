#ifndef SPININTERACTIONVERTEX_H
#define SPININTERACTIONVERTEX_H

// SpinInteractionVertex
//
// Interaction between a pair of nodes each containing one Spin.
// Holds the strength of the interaction.
//
// Seto Balian 21/11/2013


#include <utility>
#include <string>

class SpinInteractionVertex
{

private:
  std::pair<unsigned int,unsigned int> labels_;
  double strength_; // in M rad s-1
  std::string interaction_type_; // See SpinInteractions for allowed values

public:

  SpinInteractionVertex();
  
  SpinInteractionVertex(const unsigned int label1,
                         const unsigned int label2,
                         const std::string & interaction_type,
                         const double strength);

  unsigned int get_label1() const;
  unsigned int get_label2() const;
  std::string get_interaction_type() const;
  double get_strength() const;

  void set_labels(const unsigned int label1,
                 const unsigned int label2);

  void set_label1(const unsigned int label);
  void set_label2(const unsigned int label);
  
  void set_interaction_type(const std::string & interaction_type);

  void set_strength(const double strength);

};

#endif // SPININTERACTIONVERTEX_H

