// See CCE.h for description.
// Seto Balian, Apr 15, 2015

#include "SpinDec/CCE.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

CCE::CCE() : max_truncation_order_(0),include_one_clusters_(true)
{
}

CCE::CCE(const UInt max_truncation_order,
    const auto_ptr<PulseExperiment>& pulse_experiment,
    const ClusterDatabase& cluster_database,
    const bool include_one_clusters) :
    max_truncation_order_(max_truncation_order),
    include_one_clusters_(include_one_clusters),
    pulse_experiment_(pulse_experiment->clone()),
    cluster_database_(cluster_database)
{


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
  
  TimeEvolution denominator
      (pulse_experiment_->get_time_array());
  denominator.set_evolution_ones();
  
  for (UInt i=0;i<current_subclusters.size();i++) {
    denominator = denominator * true_correlation(current_subclusters[i]);
  }
  
  return reducible_correlation(cluster)/denominator;
  
}

UInt CCE::get_max_truncation_order() const
{
  return max_truncation_order_;
}

void CCE::calculate()
{

  calculate(max_truncation_order_);
  return;
  
}

void CCE::calculate(const UInt order, const bool no_divisions)
{
    
  check_order(order);
  
  TimeEvolution result(
      pulse_experiment_->get_time_array());
    
  for (UInt i=1; i<=order;i++) {
    
    result.set_evolution_ones();
            
    for (UInt j=0;j<cluster_database_.num_clusters(i);j++) {
      
      if (no_divisions == true) {
        result = result*
            reducible_correlation(cluster_database_.get_cluster(i,j));
                
      } else {
        
        result =
            result*true_correlation(cluster_database_.get_cluster(i,j));
        
      }
      
      
    }
    product_correlations_by_order_.push_back(result);
    
  }

  return;
  
}

void CCE::calculate(const UInt order)
{
  calculate(order,false);
  return;
}

void CCE::check_order(const UInt order) const
{
  if (order < 1) {
    Errors::quit("CCE input order < 1");
  }
  
  if (order>max_truncation_order_) {
    Errors::quit("CCE input order > truncation order");
  }
  
  return;

}


TimeEvolution CCE::evolution(const UInt order) const
{
  
  if (product_correlations_by_order_.empty()) {
    Errors::quit("CCE not calculated");
  }
  
  check_order(order);
  
  TimeEvolution result = product_correlations_by_order_[0];
  result.set_evolution_ones();
  
  for (UInt i=1;i<=order;i++) {
    result = result*product_correlations_by_order_[i-1];
  }
  
  return result;
  
}

const ClusterDatabase& CCE::get_database() const
{
  return cluster_database_;
}


} // namespace SpinDec

