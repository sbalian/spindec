// See CCE.h for description.
// Seto Balian, Sep 3, 2014

#include "SpinDec/CCE.h"

namespace SpinDec
{

CCE::CCE() : truncation_order_(0)
{
}

CCE::CCE(const UInt truncation_order, const CSDProblem& csd_problem) :
    truncation_order_(truncation_order),
    csd_problem_(csd_problem)
{
  database_ = ClusterDatabase(csd_problem_.get_spin_bath(),truncation_order_);
}

TimeEvolution CCE::reducible_correlation(const Cluster& cluster)
{
  
  // if already calculated, return the calculated evolution
  if ( database_.is_solved(cluster) ) {
    return database_.get_time_evolution(cluster);
  }
  
  // otherwise, calculate the reduced problem
    
  // get the reduced problem
  SpinSystem reduced_problem = csd_problem_.get_reduced_problem(
      cluster.get_labels());
  
  // calculate the experiment
  TimeEvolution evolution = csd_problem_.get_pulse_experiment()
          ->time_evolution(reduced_problem.get_state());
  
  // store result in database
  database_.set_time_evolution(cluster,evolution);
  database_.solved(cluster);
  
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
        reducible_correlation(current_subclusters[i]) );
  }
  
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
      csd_problem_.get_pulse_experiment()->get_time_array());
  result.set_evolution_ones();
  
  for (UInt i=1; i<=truncation_order_;i++) {
    for (UInt j=0;j<database_.num_clusters(i);j++) {
      result = result*true_correlation(database_.get_cluster(j,i));
    }
  }
  return result;
}

} // namespace SpinDec

