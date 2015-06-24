#ifndef CLUSTERDATABASEENTRY_H_
#define CLUSTERDATABASEENTRY_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/Cluster.h"
#include "SpinDec/TimeEvolution.h"

namespace SpinDec
{

/// Entry for ClusterDatabase.
class ClusterDatabaseEntry
{
private:
  Cluster cluster_;
  TimeEvolution time_evolution_;
  bool is_solved_;
  
public:
  
  ClusterDatabaseEntry();
  /// is_solved_ = false.
  explicit ClusterDatabaseEntry(const Cluster& cluster);
  
  const Cluster& get_cluster() const;
  
  bool is_solved() const;
  
  const TimeEvolution& get_time_evolution() const;
  void set_time_evolution(const TimeEvolution& time_evolution);
  
};

} // namespace SpinDec

#endif // CLUSTERDATABASEENTRY_H_
