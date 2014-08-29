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
// Seto Balian, Aug 29, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/CSDProblem.h"
#include "SpinDec/ClusterDatabase.h"

namespace SpinDec
{

class CCE
{
private:
  
  UInt truncation_order_;
  CSDProblem csd_problem_;
  
  ClusterDatabase database_;
  
public:
  
  CCE();
  CCE(const UInt truncation_order,
      const CSDProblem& csd_problem,
      const double pairing_cutoff);
  
  UInt get_truncation_order() const;
  
  
};

} // namespace SpinDec

#endif // CCE_H_
