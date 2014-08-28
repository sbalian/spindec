#ifndef CLUSTER_H_
#define CLUSTER_H_

// SpinDec::Cluster
//
// Contains labels for a cluster of spins.
// Labels are always sorted in increasing order.
//
// Seto Balian, Aug 28, 2014

#include "SpinDec/typedefs.h"

#include <iostream>
#include <vector>

namespace SpinDec
{

class Cluster
{
private:
  
  UIntArray labels_;
  
  vector< UIntArray > subsets(const UIntArray& v, const UInt size) const;
  vector< UIntArray > subsets(const UIntArray& v) const;
  
public:
  
  Cluster();
  explicit Cluster(const UIntArray& labels);
  
  void add(const UInt label);
  bool operator==( const Cluster& rhs) const;
  
  // number of labels
  UInt num_spins() const;
  
  UInt get_label(const UInt index) const;
  
  const UIntArray& get_labels() const;
  
  // Print with cout
  friend std::ostream& operator<<(std::ostream& os,
      Cluster const & cluster);
  
  // get all subsets (exludes the empty set)
  vector<Cluster> subsets() const;
  // get proper subsets (excludes the empty set)
  vector<Cluster> proper_subsets() const;
  
};

} // namespace SpinDec

#endif // CLUSTER_H_
