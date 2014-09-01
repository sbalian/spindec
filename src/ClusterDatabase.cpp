// See ClusterDatabase.h for description.
// Seto Balian, Sep 1, 2014

// TODO errors and checks ...
// TODO comments and modifiy legacy code comments ...

#include "SpinDec/ClusterDatabase.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

void ClusterDatabase::init(const SpinBath& spin_bath, const UInt max_order)
{
  if (max_order == 0) {
    Errors::quit("Max order cannot be zero.");
  }
  
  const UInt num_sites = spin_bath.num_spin_systems();
  
  // make 1-clusters (clusters of order 1, ie 1 bath spin system)
  
  vector<Cluster> one_clusters;
  
  for (UInt i=0;i<num_sites;i++) {
    Cluster cluster;
    cluster.add(i);
    one_clusters.push_back(cluster);
  }
  
  clusters_.push_back(one_clusters);
  
  if (max_order == 1) {
    return;
  }
  
  // make 2-clusters
  
  vector<Cluster> two_clusters;
  vector < std::pair<UInt,UInt> > pair_labels;
  
  // pairs of sites
  for (UInt i = 0; i<num_sites;i++) {
    UInt j = 0;
    while (j<i) {
      
      ThreeVector separation =
          spin_bath.get_crystal_structure().get_site_vector(i) -
          spin_bath.get_crystal_structure().get_site_vector(j);
      
      if (!( is_within_distance(separation,spin_bath.get_pairing_cutoff()))) {
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
    two_clusters.push_back(cluster);
  }

  clusters_.push_back(two_clusters);
  
  if (max_order == 2) {
    return;
  }
    
  // Make the larger clusters
  
  // For each cce order, loop over cce orders next level down,
  // check all spin separations if at least one distance below threshold,
  // then include the cluster
  
  // loop over cce orders (exclude 2-clusters - already added)
  for (UInt i=3;i<=max_order;i++) {
    // current order to add
    vector<Cluster> n_clusters;
    
    UInt prev_order = i - 1;
    UInt num_prev_clusters = num_clusters(prev_order);
    
    // loop over clusters one order down
    for (UInt j=0;j<num_prev_clusters;j++) {
      
      // get the cluster
      Cluster prev_cluster = get_cluster(prev_order,j);
      UIntArray prev_spin_labels = prev_cluster.get_labels();
      
      // for each cluster,
      // loop over sites in the lattice
      for (UInt k=0;k<num_sites;k++) {
        
        // get the site to potentially add
        ThreeVector site_to_add =
            spin_bath.get_crystal_structure().get_site_vector(k);
        
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
        
        // if at least one distance from the check site is smaller than
        // the separation cutoff, add
        bool distance_check = false;
        
        for (UInt l=0;l<prev_order;l++) {
          
          UInt spin_label = prev_spin_labels[l];
          ThreeVector to_check =
              spin_bath.get_crystal_structure().get_site_vector(spin_label);
                    
          // found one distance smaller than threshold,
          // leave loop and add cluster
          distance_check = is_within_distance(to_check-site_to_add,
              spin_bath.get_pairing_cutoff());
          if (distance_check == true) {
            break;
          }
          
        }
        
        if (distance_check == true) {
          vector<UInt> new_spin_labels = prev_spin_labels;
          new_spin_labels.push_back(k);
          
          // now, check if cluster already exists
          // if it does not then add
          Cluster to_add(new_spin_labels);
          //cout << n_clusters.exists(to_add) << endl;
          if (!exists(to_add)) {
//            for (unsigned int r=0;r<new_spin_labels.size();r++) {
//              cout << new_spin_labels[r] << "\t";
//            }
//            cout << endl;
//            cout << i << endl;
            // TODO Warning, maybe sorting inefficiency here ...
            Cluster new_cluster(new_spin_labels);
            n_clusters.push_back(new_cluster);
            
            // now get the subsets of this current cluster
            
            vector<Cluster> sub_clusters = new_cluster.subsets();
            
            const UInt sub_clusters_size  =sub_clusters.size();
            for (UInt l =0;l<sub_clusters_size;l++) {
              const UInt sub_order = sub_clusters[l].num_spins();
              if (sub_order == i) {
                continue;
              }
              Cluster sub_cluster = sub_clusters[l];

              if  (!exists(sub_cluster)) {
                clusters_[sub_order-1].push_back(sub_cluster);
              }
            }
          }
            
            
        }

        }
        
      }
      clusters_.push_back(n_clusters);
    }
  
  return;
}


ClusterDatabase::ClusterDatabase()
{
}

ClusterDatabase::ClusterDatabase(const SpinBath& spin_bath,
    const UInt max_order)
{
  
  init(spin_bath,max_order);
  
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

bool ClusterDatabase::is_solved(const UInt order,
    const UInt index) const
{
  return is_solved_[order-1][index];
}

void ClusterDatabase::add_cluster(const Cluster& cluster)
{
  const UInt order = cluster.num_spins();
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

bool ClusterDatabase::exists(const Cluster& cluster) const
{
  const UInt order = cluster.num_spins();
  for (UInt i =0;i<num_clusters(order);i++) {
    if (cluster == get_cluster(order,i)) {
      return true;
    }
  }
  return false;
}

UInt ClusterDatabase::get_index(const Cluster& cluster) const
{
  
  const UInt order = cluster.num_spins();
  
  for (UInt i =0;i<num_clusters(order);i++) {
    if (cluster == get_cluster(order,i)) {
      return i;
    }
  }
  
  Errors::quit("Cluster does not exist.");
  return 0;
  
}

const Cluster& ClusterDatabase::get_cluster(const Cluster& cluster) const
{
  return get_cluster(cluster.num_spins(),get_index(cluster));
}

const TimeEvolution& ClusterDatabase::get_time_evolution(
    const Cluster& cluster) const
{
  return get_time_evolution(cluster.num_spins(),get_index(cluster));
}

bool ClusterDatabase::is_solved(const Cluster& cluster) const
{
  return is_solved(cluster.num_spins(),get_index(cluster));
}

void ClusterDatabase::set_time_evolution(const Cluster& cluster,
    const TimeEvolution& time_evolution)
{
  set_time_evolution(cluster.num_spins(),get_index(cluster),time_evolution);
  return;
}

void ClusterDatabase::solved(const Cluster& cluster)
{
  solved(cluster.num_spins(),get_index(cluster));
  return;
}

UInt ClusterDatabase::max_order() const
{
  return clusters_.size();
}

UInt ClusterDatabase::num_clusters(const UInt order) const
{
  if (order == 0) {
    Errors::quit("Order cannot be zero.");
  }
  
  return clusters_[order-1].size();
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

bool ClusterDatabase::is_within_distance(const ThreeVector& r,
    const double distance) const
{
  if ( r.norm() <= distance ) {
    return 1;
  } // else
      return 0;
}


void ClusterDatabase::print(const UInt order, const UInt index) const
{
  cout << get_cluster(order,index) << endl;
}

} // namespace SpinDec

