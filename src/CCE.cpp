// See CCE.h for description.
// Seto Balian, Sep 10, 2014

#include "SpinDec/CCE.h"

namespace SpinDec
{

CCE::CCE() : truncation_order_(0)
{
}

CCE::CCE(const UInt truncation_order,
    const auto_ptr<PulseExperiment>& pulse_experiment) :
    truncation_order_(truncation_order),
    pulse_experiment_(pulse_experiment->clone())
{

  cluster_database_ = ClusterDatabase(pulse_experiment->
      get_csd_problem().get_spin_bath(),truncation_order_);

}

TimeEvolution CCE::reducible_correlation(const Cluster& cluster)
{
  
  
  // if already calculated, return the calculated evolution
  if ( cluster_database_.is_solved(cluster) ) {
    return cluster_database_.get_time_evolution(cluster);
  }

  // otherwise, calculate
  TimeEvolution evolution =
      pulse_experiment_->time_evolution(cluster.get_labels());

  // store result in database
  cluster_database_.set_time_evolution(cluster,evolution);
  return evolution;
  
}

TimeEvolution CCE::true_correlation(const Cluster& cluster)
{
  const UInt current_order = cluster.num_spins();
  
  if (current_order == 1) {
    return reducible_correlation(cluster);
  }
  
  
  // get the next orders down
  vector< Cluster > current_subclusters = cluster.proper_subsets();
  
  vector< TimeEvolution > divisors;
  for (UInt i=0;i<current_subclusters.size();i++) {
    divisors.push_back(
        true_correlation(current_subclusters[i]) );
  }

  //cout << divisors.size() << endl;


  TimeEvolution denominator = divisors[0];
  for (UInt i=1;i<divisors.size();i++) {
    denominator = denominator*divisors[i];
  }
  
  return reducible_correlation(cluster)/denominator;
  
}

UInt CCE::get_truncation_order() const
{
  return truncation_order_;
}

TimeEvolution CCE::calculate()
{

  TimeEvolution result(
      pulse_experiment_->get_time_array());
  result.set_evolution_ones();
  
  for (UInt i=1; i<=truncation_order_;i++) {

    for (UInt j=0;j<cluster_database_.num_clusters(i);j++) {
      
      result = result*true_correlation(cluster_database_.get_cluster(i,j));

    }
    
  }

  return result;
}

} // namespace SpinDec

