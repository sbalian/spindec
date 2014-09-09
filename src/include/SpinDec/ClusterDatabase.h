#ifndef CLUSTERDATABASE_H_
#define CLUSTERDATABASE_H_

// SpinDec::ClusterDatabase
//
// Stores clusters and associated complex time evolutions.
// For use with SpinDec::CCE (cluster correlation expansion).
//
// TODO comment more
//
// Seto Balian, Sep 9, 2014

#include "SpinDec/typedefs.h"

#include "SpinDec/Cluster.h"
#include "SpinDec/TimeEvolution.h"
#include "SpinDec/SpinBath.h"

namespace SpinDec
{

class ClusterDatabase
{
private:
  // Clusters are stored in a 2D array by order
  // (number of spins inside a cluster).
  // The first dimension is the size of the clusters in the second dimension,
  // starting with size 1 (index 0).
  // Examples:
  // database_[i][0] is the first cluster of clusters of order i.
  // database_[0][5] is the sixth cluster of clusters of order 1.
  vector < vector<Cluster> > clusters_;
  vector < vector<TimeEvolution> > time_evolutions_;
  vector < vector<bool> > is_solved_; // is the cluster solved for?
  
  void add_cluster(const Cluster& cluster);
  
  // is |r|<= distance ?
  bool is_within_distance(const ThreeVector& r, const double distance) const;
  
  void init(const SpinBath& spin_bath, const UInt max_order);
  
  
  void set_time_evolution(const UInt order, const UInt index,
      const TimeEvolution& time_evolution);
  void solved(const UInt order, const UInt index);
  
  UInt get_index(const Cluster& cluster) const;

  
public:
  
  ClusterDatabase();
  ClusterDatabase(const SpinBath& spin_bath, const UInt max_order);
  
  bool exists(const Cluster& cluster) const;
  
  const Cluster& get_cluster(const Cluster& cluster) const;
  const TimeEvolution& get_time_evolution(const Cluster& cluster) const;
  bool is_solved(const Cluster& cluster) const;
  
  void set_time_evolution(const Cluster& cluster,
      const TimeEvolution& time_evolution);
  void solved(const Cluster& cluster);
  
  UInt max_order() const;
  UInt num_clusters(const UInt order) const;
  
  void print() const;
  void print(const UInt order) const;
  void print(const UInt order, const UInt index) const;
  
  const Cluster& get_cluster(const UInt order, const UInt index) const;
  const TimeEvolution& get_time_evolution(const UInt order,
      const UInt index) const;
  bool is_solved(const UInt order, const UInt index) const;
  
};

} // namespace SpinDec

#endif // CLUSTERDATABASE_H_
