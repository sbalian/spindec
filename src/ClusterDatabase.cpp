// See ClusterDatabase.h for description.
// Seto Balian, Feb 11, 2015

// TODO errors and checks ...
// TODO comments and modifiy legacy code comments ...
// TODO too much repeat code ... needs testing and polishing, optimize

#include "SpinDec/ClusterDatabase.h"
#include "SpinDec/Errors.h"
#include "SpinDec/BoostEigen.h"

namespace SpinDec
{

UInt ClusterDatabase::get_index(const Cluster& cluster) const
{
  
  const UInt order = cluster.num_spins();
  if (!is_order_built(order)) {
    Errors::quit("Clusters of given order not built.");
  }
  
  for (UInt i=0;i<database_.find(order)->second.size();i++) {
    
    if (database_.find(order)->second[i].get_cluster() == cluster) {
      return i;
    }
    
  }
  
  Errors::quit("Cluster not found.");
  return 0;
  
}


void ClusterDatabase::add_unsolved_entry(const Cluster& cluster)
{
  
  if ( cluster_exists(cluster) ) {
    Errors::quit("Cluster database entry already exists.");
    return;
  }
  
  // get order
  const UInt order = cluster.num_spins();
  
  vector<ClusterDatabaseEntry> empty_vector;
  
  if (!is_order_built(order)) {
    database_.insert(
        pair< UInt, vector<ClusterDatabaseEntry> >(order,empty_vector) );
  }
  
  if (is_order_built(order)) {
    database_.find(order)->second.push_back(ClusterDatabaseEntry(cluster));
  }
  
  return;
  
}

bool ClusterDatabase::cluster_exists(const Cluster& cluster) const
{
  
  const UInt order = cluster.num_spins();
  if (!is_order_built(order)) {
    return false;
  }
  
  // TODO repeat code  
  
  for (UInt i=0;i<database_.find(order)->second.size();i++) {
    
    if (database_.find(order)->second[i].get_cluster() == cluster) {
      
      return true;
    }
    
  }
  
  return false;
  
}

ClusterDatabase::ClusterDatabase() : max_order_(0), max_cluster_radius_(0.0)
{
}

ClusterDatabase::ClusterDatabase(const SpinBath& spin_bath,
    const UInt max_order,const double max_cluster_radius) :
        max_order_(max_order),spin_bath_(spin_bath),
        max_cluster_radius_(max_cluster_radius)
{
  build();
}

void ClusterDatabase::build()
{
  if (max_order_ == 0) {
    Errors::quit("Max order cannot be zero.");
  }
  
  const UInt num_sites = spin_bath_.num_bath_states();
  
  // first make 1-clusters (clusters of order 1, ie 1 bath spin system)
  vector<ClusterDatabaseEntry> one_clusters;
  
  for (UInt i=0;i<num_sites;i++) {
    Cluster cluster;
    cluster.add(i);
    add_unsolved_entry(cluster);
  }
  
  // if the maximum order is 1 clusters, then exit
  if (max_order_ == 1) {
    return;
  }
  
  // now make 2-clusters
  
  //vector<Cluster> two_clusters;
  vector < std::pair<UInt,UInt> > pair_labels;
  
  // pairs of sites
  for (UInt i = 0; i<num_sites;i++) {
    UInt j = 0;
    while (j<i) {
      
      ThreeVector separation =
          spin_bath_.get_crystal_structure().get_site_vector(i) -
          spin_bath_.get_crystal_structure().get_site_vector(j);
      
      if (!( BoostEigen::isWithinDistance(separation,
          max_cluster_radius_))) {
       j+=1;
       continue;
      }
      
      // j always smaller ...
      pair_labels.push_back( std::pair<UInt,UInt> (j,i) );
      j+=1;
      
    }
  }

  const UInt num_pairs = pair_labels.size();
  
  for (UInt i=0 ; i<num_pairs; i++) {
    Cluster cluster;
    cluster.add(pair_labels[i].first);
    cluster.add(pair_labels[i].second); // inefficient add method sorting ...
    add_unsolved_entry(cluster);
  }
  
  if (max_order_ == 2) {
    return;
  }
    
  // Make the larger clusters
  
  // For each cce order, loop over cce orders next level down,
  // check all spin separations; if ALL separations below threshold,
  // then include the cluster
  
  // loop over cce orders (exclude 2-clusters - already added)
  for (UInt i=3;i<=max_order_;i++) {
    
    bool found_at_least_one_cluster = false;
    
    UInt prev_order = i - 1;
    UInt num_prev_clusters = num_clusters(prev_order);
    
    // loop over clusters one order down
    for (UInt j=0;j<num_prev_clusters;j++) {
      
      // get the cluster
      ClusterDatabaseEntry prev_entry = get_entry(prev_order,j);
      UIntArray prev_spin_labels = prev_entry.get_cluster().get_labels();
      
      // for each cluster,
      // loop over sites in the lattice
      for (UInt k=0;k<num_sites;k++) {
        
        // get the site to potentially add
        ThreeVector site_to_add =
            spin_bath_.get_crystal_structure().get_site_vector(k);
        
        // loop over labels of cluster checking the new site
        
        // if the spin is already in the cluster, don't add
        bool found_duplicate = false;
        for (UInt l=0;l<prev_order;l++) {
          
          UInt spin_label = prev_spin_labels[l];
          
          if (spin_label == k) {
            found_duplicate = true;
            break;
          }
          
        }
        if (found_duplicate == true) {
          continue;
        }
        
        // if ALL distances from the check site are smaller than
        // the separation cutoff, add
        vector<bool> distance_check;
        
        for (UInt l=0;l<prev_order;l++) {
          
          UInt spin_label = prev_spin_labels[l];
          ThreeVector to_check =
              spin_bath_.get_crystal_structure().get_site_vector(spin_label);
                    
          distance_check.push_back(
              BoostEigen::isWithinDistance(to_check-site_to_add,
              max_cluster_radius_));
          
        }
        
        bool ready_to_add = distance_check[0];
        for (UInt l=1;l<prev_order;l++) {
          ready_to_add*=distance_check[l];
        }
        
        if (ready_to_add == true) {
          vector<UInt> new_spin_labels = prev_spin_labels;
          new_spin_labels.push_back(k);
          
          // now, check if cluster already exists
          // if it does not then add
          Cluster to_add(new_spin_labels);
          //cout << n_clusters.exists(to_add) << endl;
          
          
          if (!cluster_exists(to_add)) {
//            for (unsigned int r=0;r<new_spin_labels.size();r++) {
//              cout << new_spin_labels[r] << "\t";
//            }
//            cout << endl;
//            cout << i << endl;
            // TODO Warning, maybe sorting inefficiency here ...
            Cluster new_cluster(new_spin_labels);
            add_unsolved_entry(new_cluster);
            found_at_least_one_cluster = true;
            
            // Should not need this ...
            // now get the subsets of this current cluster
            
//            vector<Cluster> sub_clusters = new_cluster.subsets();
//            
//            const UInt sub_clusters_size  =sub_clusters.size();
//            for (UInt l =0;l<sub_clusters_size;l++) {
//              const UInt sub_order = sub_clusters[l].num_spins();
//              if (sub_order == i) {
//                continue;
//              }
//              Cluster sub_cluster = sub_clusters[l];
//
//              if  (!cluster_exists(sub_cluster)) {
//                add_unsolved_entry(sub_cluster);
//              }
//            }
            
          }
            
            
        }

        }
        
      }
    
    if (found_at_least_one_cluster == false) {
      Errors::quit("Could not find any clusters for maximum CCE order.");
    }
    
    }
  
  
  return;

}

const ClusterDatabaseEntry& ClusterDatabase::get_entry(
    const UInt order,
    const UInt index) const
{
  
  if (!is_order_built(order)) {
    Errors::quit("Clusters of given order not built.");
  }
  
  if (index >= database_.find(order)->second.size()) {
    Errors::quit("Entry not found.");
  }
  
  return database_.find(order)->second[index];
  
}

void ClusterDatabase::set_time_evolution(const Cluster& cluster,
    const TimeEvolution& time_evolution)
{
  
  const UInt order = cluster.num_spins();
  const UInt index = get_index(cluster);
  
  database_[order][index].set_time_evolution(time_evolution);
  
  return;
  
}

bool ClusterDatabase::is_solved(const Cluster& cluster) const
{
  const UInt order = cluster.num_spins();
  const UInt index = get_index(cluster);
  
  return database_.find(order)->second[index].is_solved();

}

UInt ClusterDatabase::get_max_order() const
{
  return max_order_;
}

UInt ClusterDatabase::num_clusters(const UInt order) const
{
  if (!is_order_built(order)) {
    Errors::quit("Clusters of given order not built.");
  }
  return database_.find(order)->second.size();
}

//const ClusterDatabaseEntry& ClusterDatabase::get_entry(
//    const Cluster& cluster) const
//{
//}

void ClusterDatabase::print() const
{
  
  database_map::const_iterator it;
  for (it=database_.begin();it!=database_.end();it++) {
    const UInt order = it->first;
    
    cout << "Clusters of order " << order << ":\n";
    
    for (UInt i=0;i<num_clusters(order);i++) {
      cout << it->second[i].get_cluster() << endl;
    }
    
  }
  
  return;
  
}

bool ClusterDatabase::is_order_built(const UInt order) const
{
  database_map::const_iterator it =
      database_.find(order);
  return it!=database_.end();
}

const TimeEvolution& ClusterDatabase::get_time_evolution(
    const Cluster& cluster) const
{
  const UInt order = cluster.num_spins();
  const UInt index = get_index(cluster);
  
  return database_.find(order)->second[index].get_time_evolution();

}

const Cluster& ClusterDatabase::get_cluster(const UInt order,
    const UInt index) const
{
  return get_entry(order,index).get_cluster();
}


} // namespace SpinDec

