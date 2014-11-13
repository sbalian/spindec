// See CCE.h for description.
// Seto Balian, Nov 13, 2014

#include "SpinDec/CCE.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

CCE::CCE() : truncation_order_(0),include_one_clusters_(true)
{
}

CCE::CCE(const UInt truncation_order,
    const auto_ptr<PulseExperiment>& pulse_experiment,
    const double pairing_cutoff,
    const bool include_one_clusters) :
    truncation_order_(truncation_order),
    include_one_clusters_(include_one_clusters),
    pulse_experiment_(pulse_experiment->clone())
{

  cluster_database_ = ClusterDatabase(pulse_experiment->
      get_csd_problem().get_spin_bath(),truncation_order_,pairing_cutoff);

}

TimeEvolution CCE::reducible_correlation(const Cluster& cluster)
{
  
  if ( (include_one_clusters_ == false) && (cluster.num_spins() == 1) ) {
    TimeEvolution no_decay(pulse_experiment_->get_time_array());
    no_decay.set_evolution_ones();
    return no_decay;
  }
  
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

void CCE::calculate()
{

  TimeEvolution result(
      pulse_experiment_->get_time_array());
    
  for (UInt i=1; i<=truncation_order_;i++) {
    
    result.set_evolution_ones();
    
    if (include_one_clusters_ == false) {
      if (i==1) {continue;}
    }
    
    for (UInt j=0;j<cluster_database_.num_clusters(i);j++) {
      
      result = result*true_correlation(cluster_database_.get_cluster(i,j));
      
    }
    
    product_true_correlations_by_order_.push_back(result);
    
  }
    
  return;
  
}

TimeEvolution CCE::evolution(const UInt order) const
{
  
  if (product_true_correlations_by_order_.empty()) {
    Errors::quit("CCE not calculated");
  }
  
  if (order < 1) {
    Errors::quit("CCE input order < 1");
  }
  
  if (order>truncation_order_) {
    Errors::quit("CCE input order > truncation order");
  }
  
  TimeEvolution result = product_true_correlations_by_order_[0];
  result.set_evolution_ones();
  
  if (include_one_clusters_ == true) {
    for (UInt i=1;i<=order;i++) {
      result = result*product_true_correlations_by_order_[i-1];
    }
  } else {
    
      for (UInt i=2;i<=order;i++) {
        result = result*product_true_correlations_by_order_[i-2];
        
      }
      
  }
  
  
  return result;
  
}

} // namespace SpinDec

