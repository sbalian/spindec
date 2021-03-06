#ifndef CSDPROBLEM_H_
#define CSDPROBLEM_H_

// Seto Balian, Jun 24, 2015

// TODO Generalize for more than a single spin bath
// TODO Comment more

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/SpinSystem.h"
#include "SpinDec/SpinBath.h"
#include "SpinDec/UniformMagneticField.h"
#include "SpinDec/SpinInteractionEdge.h"

namespace SpinDec
{

/**
 * \brief Central spin decoherence problem.
 * 
 * Currently supports a single spin bath. 
 * 
 */
class CSDProblem
{
private:

  shared_ptr<SpinSystemBase> central_spin_system_;
  SpinBath spin_bath_;
  
  UniformMagneticField field_;

  /**
   * Edges should comply as in the join methods for SpinInteractionGraph,
   * with the first graph being the central spin graph and the second being
   * the graph for a single bath system.
   */
  vector<SpinInteractionEdge> system_bath_edges_;
  
  void init(const shared_ptr<SpinSystemBase>& central_spin_system_base,
      const SpinBath& spin_bath,
      const vector<SpinInteractionEdge>& system_bath_edges,
      const UniformMagneticField& field);
  
  vector<SpinInteractionEdge> make_system_bath_edges(const UInt order,
      const SpinInteractionEdge& edge) const;
  
  vector<SpinInteractionEdge> make_system_bath_edges(const UInt order) const;
  
  vector< pair< UInt, SpinSystem > > reduced_problems_;
  
  SpinSystem construct_reduced_problem(const UInt order) const;
  
  UIntArray get_bath_vertex_labels(const UInt order) const;

public:
  
  CSDProblem();
  CSDProblem(const CSDProblem& csd_problem);
  CSDProblem& operator=(const CSDProblem& csd_problem);

  CSDProblem(const shared_ptr<SpinSystemBase>& central_spin_system_base,
      const SpinBath& spin_bath,
      const vector<SpinInteractionEdge>& system_bath_edges,
      const UniformMagneticField& field);
  CSDProblem(const shared_ptr<SpinSystemBase>& central_spin_system_base,
      const SpinBath& spin_bath,
      const SpinInteractionEdge& system_bath_edge,
      const UniformMagneticField& field);
  
  void set_central_spin_state(const SpinState& spin_state) const;

  SpinSystem get_reduced_problem(const UIntArray bath_indices);

  const SpinBath& get_spin_bath() const;
  shared_ptr<SpinSystemBase> get_central_spin_system() const;

};

} // namespace SpinDec

#endif // CSDPROBLEM_H_
