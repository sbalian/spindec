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
//
// Seto Balian, Sep 2, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/CSDProblem.h"
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

  CSDProblem csd_problem_;
  
  ClusterDatabase database_;
  
  TimeEvolution reducible_correlation(const Cluster& cluster);
  TimeEvolution true_correlation(const Cluster& cluster);
  
  vector<SpinSystem> reduced_problems_;
  
  const SpinSystem& get_reduced_problem(const UInt order) const;

public:
  
  CCE();
  CCE(const TimeArray& time_array,
      const UInt truncation_order,
      const CSDProblem& csd_problem);
  
  UInt get_truncation_order() const;
  
  
};

} // namespace SpinDec

#endif // CCE_H_
