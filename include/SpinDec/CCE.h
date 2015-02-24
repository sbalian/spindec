#ifndef CCE_H_
#define CCE_H_

// SpinDec::CCE
//
// Solves for the central spin decoherence problem using the cluster correlation
// expansion (CCE).
//
// CCE References:
// - Phys. Rev. B 74, 035322 (2006)
// - Phys. Rev. B 78, 085315 (2008)
// - Phys. Rev. B 78, 129901(E) (2008)
// - Phys. Rev. B 79, 115320 (2009)
// - Phys. Rev. B 86, 035452 (2012)
//
// TODO Comment more
// TODO have experiment instead of pulse experiment?
//
// Seto Balian, Feb 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/ClusterDatabase.h"
#include "SpinDec/PulseExperiment.h"
#include "SpinDec/TimeEvolution.h"

namespace SpinDec
{

class CCE
{
private:
  
  void check_order(const UInt order) const;
  
  vector<TimeEvolution> product_correlations_by_order_;
  
  // maximum CCE truncation order
  UInt max_truncation_order_;
  bool include_one_clusters_;

  auto_ptr<PulseExperiment> pulse_experiment_;
  
  ClusterDatabase cluster_database_;
  
  TimeEvolution reducible_correlation(const Cluster& cluster);
  TimeEvolution true_correlation(const Cluster& cluster);
  
  //void print(const string& file_name, const char option) const;
  
public:
  
  CCE();
  CCE(const UInt max_truncation_order,
      const auto_ptr<PulseExperiment>& pulse_experiment,
      const ClusterDatabase& cluster_database,
      const bool include_one_clusters);
    
  UInt get_max_truncation_order() const;
  
  // Input CCE truncation order to calculate, cannot be greater than
  // max_truncation_order_
  void calculate(const UInt order);
  void calculate(const UInt order, const bool no_divisions);
  // calls calculate(max_truncation_order_,false)
  void calculate();
  
  // get the time evolution (has to be calculated with above method first)
  TimeEvolution evolution(const UInt order) const;
  
  const ClusterDatabase& get_database() const;
  
};

} // namespace SpinDec

#endif // CCE_H_
