// See ClusterDatabaseEntry.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/ClusterDatabaseEntry.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

const Cluster& ClusterDatabaseEntry::get_cluster() const
{
  return cluster_;
}

bool ClusterDatabaseEntry::is_solved() const
{
  return is_solved_;
}

const TimeEvolution& ClusterDatabaseEntry::get_time_evolution() const
{
  if (is_solved_ == false) {
    Errors::quit("Have not solved for cluster.");
  }
  return time_evolution_;
}

ClusterDatabaseEntry::ClusterDatabaseEntry() : is_solved_(false)
{
}

ClusterDatabaseEntry::ClusterDatabaseEntry(const Cluster& cluster) :
        cluster_(cluster),time_evolution_(TimeEvolution()),is_solved_(false)
{
}

void ClusterDatabaseEntry::set_time_evolution(
    const TimeEvolution& time_evolution)
{
  time_evolution_ = time_evolution;
  is_solved_ = true;
  return;
}


} // namespace SpinDec

