#ifndef CCE_H_
#define CCE_H_

// SpinDec::CCE
//
// Solves for the central spin decoherence problem using the cluster correlation
// expansion (CCE). Currently supports a single spin bath. TODO Generalize.
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
// Seto Balian, Aug 28, 2014

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/SpinSystem.h"
#include "SpinDec/SpinBath.h"
#include "SpinDec/UniformMagneticField.h"
#include "SpinDec/SpinInteractionEdge.h"

namespace SpinDec
{

class CCE
{
private:
  
  UInt truncation_order_;
  
  SpinSystem central_spin_system_;
  SpinBath spin_bath_;
  
  UniformMagneticField field_;
  
  // Edges should comply as in the join methods for SpinInteractionGraph,
  // with the first graph being the central spin graph and the second being
  // the graph for a single bath system.
  vector<SpinInteractionEdge> system_bath_edges_;
  
  vector<SpinSystem> reduced_problems_;
  
  void init(const UInt truncation_order,
      const auto_ptr<SpinSystemBase>& central_spin_system_base,
      const SpinBath& spin_bath,
      const vector<SpinInteractionEdge>& system_bath_edges,
      const UniformMagneticField& field);
  
  vector<SpinInteractionEdge> get_system_bath_edges(const UInt order,
      const SpinInteractionEdge& edge) const;
  
  vector<SpinInteractionEdge> get_system_bath_edges(const UInt order) const;
  
public:
  
  CCE();
  CCE(const UInt truncation_order,
      const auto_ptr<SpinSystemBase>& central_spin_system_base,
      const SpinBath& spin_bath,
      const vector<SpinInteractionEdge>& system_bath_edges,
      const UniformMagneticField& field);
  CCE(const UInt truncation_order,
      const auto_ptr<SpinSystemBase>& central_spin_system_base,
      const SpinBath& spin_bath,
      const SpinInteractionEdge& system_bath_edge,
      const UniformMagneticField& field);

  const SpinSystem& get_reduced_problem(const UInt order) const;
  
};

} // namespace SpinDec

#endif // CCE_H_
