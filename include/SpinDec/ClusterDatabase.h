#ifndef CLUSTERDATABASE_H_
#define CLUSTERDATABASE_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"

#include "SpinDec/Cluster.h"
#include "SpinDec/TimeEvolution.h"
#include "SpinDec/SpinBath.h"
#include "SpinDec/ClusterDatabaseEntry.h"

namespace SpinDec
{

typedef map <UInt , vector<ClusterDatabaseEntry> > database_map;

/**
 * \brief Stores clusters and associated complex time evolutions.
 * 
 * For use with SpinDec::CCE (cluster correlation expansion).
 * Has two build methods, one with a local cluster cutoff where the maximum
 * separation between any pair of spins in any cluster is cluster_cutoff.
 * The other (global) method builds pairs with cluster_cutoff maximum
 * separation, then adds spins which are at a maximum of cluster_cutoff from
 * any of the two spins to form 3-clusters, and so on for 4-clusters etc.
 * 
 */
class ClusterDatabase
{
private:
  
  /// Maximum build order.
  UInt max_order_;
  
  SpinBath spin_bath_;
  
  /// Cluster size (order), vector of database entries. All unique clusters.
  database_map database_;
  // TODO make sure this is ensured more neatly in implementation
  
  // build the database
  
  /// Build 2-clusters.
  void build_pairs();
  /// Build 1-clusters.
  void build_ones(); 
  /// Higher order clusters with local cutoff.
  void build_with_local_cutoff();
  /// Higher order clusters with global cutoff.
  void build_with_global_cutoff();
  
  UInt get_index(const Cluster& cluster) const;
  
  /// Add cluster if it does not exist.
  void add_unsolved_entry(const Cluster& cluster);
  
  bool is_order_built(const UInt order) const;
  bool cluster_exists(const Cluster& cluster) const;
  
  /// In \f$\mbox{\AA}\f$.
  double cluster_cutoff_;
 
public:
  
  ClusterDatabase();
  
  /// Build method is "global" or "local".
  ClusterDatabase(const SpinBath& spin_bath, const UInt max_order,
      const double cluster_cutoff,const string& build_method);
  
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
