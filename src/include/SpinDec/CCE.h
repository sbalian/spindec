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
// Seto Balian, Aug 22, 2014

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/SpinSystem.h"
#include "SpinDec/SpinBath.h"
#include "SpinDec/UniformMagneticField.h"


namespace SpinDec
{

class CCE
{
private:
  
  UInt truncation_order_;
  
  SpinSystem central_spin_system_;
  SpinBath spin_bath_;
  UniformMagneticField field_;
  
  // deal with this properly
  SpinSystem combined_spin_system_;
  
public:
  
  CCE();
  CCE(const UInt truncation_order,
      const auto_ptr<SpinSystemBase>& central_spin_system_base,
      const SpinBath& spin_bath,
      const UInt interaction_label1,
      const UInt interaction_label2,
      const auto_ptr<SpinInteraction> & interaction,
      const UniformMagneticField& field);
  
  void add_system_bath_interaction(const UInt interaction_label1,
      const UInt interaction_label2,
      const  auto_ptr<SpinInteraction> & interaction);
  
  void solve();
  
};

} // namespace SpinDec

#endif // CCE_H_
