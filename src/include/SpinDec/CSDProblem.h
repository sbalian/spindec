#ifndef CSDPROBLEM_H_
#define CSDPROBLEM_H_

// SpinDec::CSDProblem
//
// Central spin decoherence problem.
// Currently supports a single spin bath. TODO Generalize.
//
// TODO Comment more
//
// Seto Balian, Sep 3, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/SpinSystem.h"
#include "SpinDec/SpinBath.h"
#include "SpinDec/UniformMagneticField.h"
#include "SpinDec/SpinInteractionEdge.h"
#include "SpinDec/PulseExperiment.h"

namespace SpinDec
{

class CSDProblem
{
private:

  SpinSystem central_spin_system_;
  SpinBath spin_bath_;
  
  UniformMagneticField field_;
  
  auto_ptr<PulseExperiment> pulse_experiment_;
  
  // Edges should comply as in the join methods for SpinInteractionGraph,
  // with the first graph being the central spin graph and the second being
  // the graph for a single bath system.
  vector<SpinInteractionEdge> system_bath_edges_;
  
  void init(const auto_ptr<SpinSystemBase>& central_spin_system_base,
      const SpinBath& spin_bath,
      const vector<SpinInteractionEdge>& system_bath_edges,
      const UniformMagneticField& field,
      const auto_ptr<PulseExperiment> & pulse_experiment);
  
  vector<SpinInteractionEdge> make_system_bath_edges(const UInt order,
      const SpinInteractionEdge& edge) const;
  
  vector<SpinInteractionEdge> make_system_bath_edges(const UInt order) const;
  
  vector< pair<UInt,SpinSystem> > reduced_problems_;
  
  SpinSystem construct_reduced_problem(const UInt order) const;
  UIntArray get_bath_vertex_labels(const UInt order) const;

public:
  
  
  CSDProblem();
  CSDProblem(const auto_ptr<SpinSystemBase>& central_spin_system_base,
      const SpinBath& spin_bath,
      const vector<SpinInteractionEdge>& system_bath_edges,
      const UniformMagneticField& field,
      const auto_ptr<PulseExperiment> & pulse_experiment);
  CSDProblem(const auto_ptr<SpinSystemBase>& central_spin_system_base,
      const SpinBath& spin_bath,
      const SpinInteractionEdge& system_bath_edge,
      const UniformMagneticField& field,
      const auto_ptr<PulseExperiment> & pulse_experiment);
  
  CSDProblem(const CSDProblem& other);
  CSDProblem& operator=( const CSDProblem& other);

  SpinSystem get_reduced_problem(const UIntArray bath_indices);

  const SpinBath& get_spin_bath() const;
  const SpinSystem& get_central_spin_system() const;
  
  TimeEvolution time_evolution(const SpinSystem& reduced_problem);
  
  auto_ptr<PulseExperiment> get_pulse_experiment() const;

};

} // namespace SpinDec

#endif // CSDPROBLEM_H_
