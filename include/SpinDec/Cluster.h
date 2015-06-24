#ifndef CLUSTER_H_
#define CLUSTER_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"

#include <iostream>
#include <vector>

namespace SpinDec
{

/**
 * \brief Contains labels for a cluster of spins.
 * 
 * Labels are always sorted in increasing order.
 * 
 */
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
  
  /// Number of labels.
  UInt num_spins() const;
  
  UInt get_label(const UInt index) const;
  
  const UIntArray& get_labels() const;
  
  /// Print.
  friend std::ostream& operator<<(std::ostream& os,
      Cluster const & cluster);
  
  /// Get all subsets (exludes the empty set).
  vector<Cluster> subsets() const;
  /// Get proper subsets (excludes the empty set).
  vector<Cluster> proper_subsets() const;
  
};

} // namespace SpinDec

#endif // CLUSTER_H_
