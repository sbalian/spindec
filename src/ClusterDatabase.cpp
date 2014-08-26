// See ClusterDatabase.h for description.
// Seto Balian, Aug 26, 2014

// TODO errors and checks ...

#include "SpinDec/ClusterDatabase.h"

#include "SpinDec/Errors.h"

namespace SpinDec
{

ClusterDatabase::ClusterDatabase()
{
}

const Cluster& ClusterDatabase::get_cluster(const UInt order,
    const UInt index) const
{
  return clusters_[order-1][index];
}

const TimeEvolution& ClusterDatabase::get_time_evolution(
    const UInt order, const UInt index) const
{
  return time_evolutions_[order-1][index];
}

const bool ClusterDatabase::is_solved(const UInt order,
    const UInt index) const
{
  return is_solved_[order-1][index];
}

void ClusterDatabase::add_cluster(const UInt order,
    const Cluster& cluster)
{
  clusters_[order-1].push_back(cluster);
  time_evolutions_[order-1].push_back(TimeEvolution());
  is_solved_[order-1].push_back(false);
  return;
}

void ClusterDatabase::set_time_evolution(const UInt order,
    const UInt index, const TimeEvolution& time_evolution)
{
  time_evolutions_[order-1][index] = time_evolution;
  return;
}

void ClusterDatabase::solved(const UInt order, const UInt index)
{
  is_solved_[order-1][index] = true;
  return;
}

bool ClusterDatabase::exists(const UInt order,
    const Cluster& cluster) const
{
  
  for (UInt i =0;i<num_clusters(order);i++) {
    if (cluster == get_cluster(order,i)) {
      return true;
    }
  }
  return false;
  
}

UInt ClusterDatabase::get_index(const UInt order,
    const Cluster& cluster) const
{
  
  for (UInt i =0;i<num_clusters(order);i++) {
    if (cluster == get_cluster(order,i)) {
      return i;
    }
  }
  
  Errors::quit("Cluster does not exist.");
  return 0;
  
}

UInt ClusterDatabase::max_order() const
{
  return clusters_.size();
}

UInt ClusterDatabase::num_clusters(const UInt order) const
{
  return clusters_[order].size();
}

void ClusterDatabase::print() const
{
  
  for (UInt i=1;i<=max_order();i++) {
    print(i);
    cout << endl;
  }
  cout << endl;
  
}

void ClusterDatabase::print(const UInt order) const
{
  cout << "Clusters of order " << order << ":\n";
  for (UInt i=0;i<num_clusters(order);i++) {
    cout << get_cluster(order,i) << endl;
  }
  cout << endl;
}

void ClusterDatabase::print(const UInt order, const UInt index) const
{
  cout << get_cluster(order,index) << endl;
}


} // namespace SpinDec

