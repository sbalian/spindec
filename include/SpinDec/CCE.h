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
// Seto Balian, Nov 6, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/ClusterDatabase.h"
#include "SpinDec/PulseExperiment.h"
#include "SpinDec/TimeEvolution.h"

namespace SpinDec
{

class CCE
{
private:
  
  TimeEvolution time_evolution_;
  
  UInt truncation_order_;
  bool include_one_clusters_;

  auto_ptr<PulseExperiment> pulse_experiment_;
  
  ClusterDatabase cluster_database_;
  
  TimeEvolution reducible_correlation(const Cluster& cluster);
  TimeEvolution true_correlation(const Cluster& cluster);
  
public:
  
  CCE();
  CCE(const UInt truncation_order,
      const auto_ptr<PulseExperiment>& pulse_experiment,
      const double pairing_cutoff,
      const bool include_one_clusters);
  
  UInt get_truncation_order() const;
  
  TimeEvolution calculate();
  
};

} // namespace SpinDec

#endif // CCE_H_
