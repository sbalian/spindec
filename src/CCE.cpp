// See CCE.h for description.
// Seto Balian, Aug 29, 2014

#include "SpinDec/CCE.h"

namespace SpinDec
{

CCE::CCE() : truncation_order_(0)
{
}

CCE::CCE(const UInt truncation_order, const CSDProblem& csd_problem,
    const double pairing_cutoff) :
    truncation_order_(truncation_order), csd_problem_(csd_problem)
{
  
  database_ = ClusterDatabase(csd_problem_.get_spin_bath(),
      pairing_cutoff,truncation_order_);
  
  
  
  
}

UInt CCE::get_truncation_order() const
{
  return truncation_order_;
}

} // namespace SpinDec

