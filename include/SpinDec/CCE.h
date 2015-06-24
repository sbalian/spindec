#ifndef CCE_H_
#define CCE_H_

// Seto Balian, Jun 24, 2015

// TODO Comment more
// TODO have experiment instead of pulse experiment?

#include "SpinDec/typedefs.h"
#include "SpinDec/ClusterDatabase.h"
#include "SpinDec/PulseExperiment.h"
#include "SpinDec/TimeEvolution.h"

namespace SpinDec
{

/**
 * \brief Solves for a CSD problem using the CCE. 
 * 
 * The cluster correlation expansion (CCE) is used to solve for a central spin
 * decoherence (CSD) problem. Relevant references are:
 * - Phys. Rev. B 74, 035322 (2006),
 * - Phys. Rev. B 78, 085315 (2008),
 * - Phys. Rev. B 78, 129901(E) (2008),
 * - Phys. Rev. B 79, 115320 (2009),
 * - Phys. Rev. B 86, 035452 (2012).
 * 
 */
class CCE
{
private:
  
  void check_order(const UInt order) const;
  
  vector<TimeEvolution> product_correlations_by_order_;
  
  /// Maximum CCE truncation order.
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
  
  /**
   * \brief Calculate the CCE.
   * 
   * Input CCE truncation order to calculate. This input cannot exceed
   * CCE::max_truncation_order_.
   * 
   */
  void calculate(const UInt order);
  void calculate(const UInt order, const bool no_divisions);
  /// Calls CCE::calculate(const UInt order,false).
  void calculate();
  
  /// Get the time evolution (has to be calculated with above method first).
  TimeEvolution evolution(const UInt order) const;
  
  const ClusterDatabase& get_database() const;
  
};

} // namespace SpinDec

#endif // CCE_H_
