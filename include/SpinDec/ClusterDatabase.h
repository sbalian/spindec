#ifndef CLUSTERDATABASE_H_
#define CLUSTERDATABASE_H_

// SpinDec::ClusterDatabase
//
// Stores clusters and associated complex time evolutions.
// For use with SpinDec::CCE (cluster correlation expansion).
//
// Has two build methods, one with a local cluster cutoff where the maximum
// separation between any pair of spins in any cluster is cluster_cutoff.
// The other (global) method builds pairs with cluster_cutoff maximum
// separation, then adds spins which are at a maximum of cluster_cutoff from
// ANY of the two spins to form 3-clusters, and so on for 4-clusters etc.
//
// Seto Balian, Feb 24, 2015

#include "SpinDec/typedefs.h"

#include "SpinDec/Cluster.h"
#include "SpinDec/TimeEvolution.h"
#include "SpinDec/SpinBath.h"
#include "SpinDec/ClusterDatabaseEntry.h"

namespace SpinDec
{

typedef map <UInt , vector<ClusterDatabaseEntry> > database_map;

class ClusterDatabase
{
private:
  
  // Maximum build order
  UInt max_order_;
  
  SpinBath spin_bath_;
  
  // cluster size (order), vector of database entries
  // all unique clusters ... TODO make sure this is ensured more neatly in the
  // implementation
  database_map database_;
  
  // build the database
  
  void build_pairs(); // build 2-clusters
  void build_ones(); // build 1-clusters
  void build_with_local_cutoff(); // higher order clusters with local cutoff
  void build_with_global_cutoff(); // higher order clusters with global cutoff
  
  UInt get_index(const Cluster& cluster) const;
  
  // add cluster if it does not exist
  void add_unsolved_entry(const Cluster& cluster);
  
  bool is_order_built(const UInt order) const;
  bool cluster_exists(const Cluster& cluster) const;
  
  double cluster_cutoff_; // Angstroms
 
 
public:
  
  ClusterDatabase();
  
  ClusterDatabase(const SpinBath& spin_bath, const UInt max_order,
      const double cluster_cutoff,const string& build_method);
  // build method is "global" or "local" (see above)
  
  
  const ClusterDatabaseEntry& get_entry(const UInt order,
      const UInt index) const;
  
  const Cluster& get_cluster(const UInt order,
      const UInt index) const;
  
  void set_time_evolution(const Cluster& cluster,
      const TimeEvolution& time_evolution);
  
  bool is_solved(const Cluster& cluster) const;

  UInt get_max_order() const;
  UInt num_clusters(const UInt order) const;
  
  const TimeEvolution& get_time_evolution(const Cluster& cluster) const;
  
  void print() const;
  
  
};

} // namespace SpinDec

#endif // CLUSTERDATABASE_H_
