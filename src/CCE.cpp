// See CCE.h for description.
// Seto Balian, Sep 2, 2014

#include "SpinDec/CCE.h"

namespace SpinDec
{

CCE::CCE() : truncation_order_(0)
{
}

CCE::CCE(const TimeArray& time_array,
    const UInt truncation_order, const CSDProblem& csd_problem) :
    time_evolution_(time_array),
    truncation_order_(truncation_order),
    csd_problem_(csd_problem)
{
  database_ = ClusterDatabase(csd_problem_.get_spin_bath(),truncation_order_);
  
  // set up the reduced problems
  for (UInt i=1;i<=truncation_order_;i++) {
    reduced_problems_(csd_problem.reduced_problem(i));
  }
  
}

TimeEvolution CCE::reducible_correlation(const Cluster& cluster)
{
  
  // if already calculated, return the calculated evolution
  if ( database_.is_solved(cluster) ) {
    return database_.get_time_evolution(cluster);
  }
  
  // otherwise, calculate the reduced problem
  
  // get the reduced problem
  const UInt order = cluster.num_spins();
  SpinSystem reduced_problem = get_reduced_problem(order);
  
  // now set the initial bath positions
  
  // get the site vectors
  vector<ThreeVector> sites;
  for (UInt i=0;i<order;i++) {
    sites.push_back(
     csd_problem_.get_spin_bath().get_crystal_structure().get_site_vector(i));
  }
  
  // get the bath vertex labels
  UIntArray bath_vertex_labels =
      csd_problem_.get_bath_vertex_labels(order);
  // get the number of bath vertices
  UInt num_bath_vertices =
      csd_problem_.get_spin_bath().get_spin_system().get_graph().num_vertices();
  
  // new positions
  vector<ThreeVector> positions;
  for (UInt i=0;i<order;i++) {
    for (UInt j=0;j<num_bath_vertices;j++) {
      positions.push_back(sites[i]);
    }
  }
  for (UInt i=0;i<bath_vertex_labels.size();i++) {
    positions[i]+=
     csd_problem_.get_spin_bath().get_spin_system().get_graph().get_position(i);
  }
  reduced_problem.update_positions(bath_vertex_labels,positions);

  // set the initial state
  // TODO this needs checking ...
  reduced_problem.set_state(csd_problem_.get_central_spin_system().get_state()
      ^csd_problem_.get_spin_bath().get_state(cluster.get_labels()));
  
  
  // TODO you are here
  // make pulse experiment member of csd problem
  
  return TimeEvolution();
  
}

TimeEvolution CCE::true_correlation(const Cluster& cluster)
{
  return TimeEvolution();
}

const SpinSystem& CCE::get_reduced_problem(const UInt order) const
{
  return reduced_problems_[order-1];
}

UInt CCE::get_truncation_order() const
{
  return truncation_order_;
}

} // namespace SpinDec

