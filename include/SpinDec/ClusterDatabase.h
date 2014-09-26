#ifndef CLUSTERDATABASE_H_
#define CLUSTERDATABASE_H_

// SpinDec::ClusterDatabase
//
// Stores clusters and associated complex time evolutions.
// For use with SpinDec::CCE (cluster correlation expansion).
//
// TODO comment more
//
// Seto Balian, Sep 26, 2014

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
    
  UInt max_order_;
  SpinBath spin_bath_;
  
  // cluster size (order), vector of database entries
  // all unique clusters ... TODO make sure this is ensured more neatly in the
  // implementation
  database_map database_;
  
  // build the database
  void build();
  
  UInt get_index(const Cluster& cluster) const;
  
  // add cluster if it does not exist
  void add_unsolved_entry(const Cluster& cluster);
  
  bool is_order_built(const UInt order) const;
  bool cluster_exists(const Cluster& cluster) const;
  
  double pairing_cutoff_;
  
  //const ClusterDatabaseEntry& get_entry(const Cluster& cluster) const;
    
public:
  
  ClusterDatabase();
  ClusterDatabase(const SpinBath& spin_bath, const UInt max_order,
      const double pairing_cutoff);
  
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
