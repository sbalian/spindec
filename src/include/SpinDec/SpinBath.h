#ifndef SPINBATH_H_
#define SPINBATH_H_

// SpinDec::SpinBath
//
// Spin bath (of a single spin species) for the central spin decoherence
// problem in a crystal. Infinite temperature, so that all states are equally
// likely.
// TODO Generalize to finite temperature; Generalize for multiple spin species?
//      or use combinations of single-spin-species baths?
// TODO comment more
// Seto Balian, Sep 1, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/CrystalStructure.h"
#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/SpinSystem.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/SpinInteraction.h"
#include "SpinDec/SpinInteractionEdge.h"

namespace SpinDec
{

class SpinBath
{
private:
  
  vector<SpinState> states_;
  
  // Positions in graph denote relative positions of atoms at a site in the
  // crystal structure ...
  SpinSystem spin_system_;
  
  // Take the graph of the spin system.
  // Consider joining the graph to itself.
  // For example, if the vertices of the original graph were 0,1,2,
  // the new graph will have vertices 0,1,2(originals),3,4,5(copies) -
  // this is like the joining methods in SpinInteractionGraph.
  // Use these new labels for the intrabath edges.
  vector<SpinInteractionEdge> intrabath_edges_;
  
  CrystalStructure crystal_structure_;
  
  void init(const CrystalStructure& crystal_structure,
      const auto_ptr<SpinSystemBase>& spin_system_base,
      const vector<SpinInteractionEdge>& intrabath_edges);
  
  vector<SpinInteractionEdge> make_intrabath_edges(const UInt order,
      const SpinInteractionEdge& intrabath_edge) const;
  
  vector<SpinInteractionEdge> make_intrabath_edges(const UInt order) const;
  
  double pairing_cutoff_;
  
public:
  SpinBath();
  SpinBath(const CrystalStructure& crystal_structure,
      const auto_ptr<SpinSystemBase>& spin_system_base,
      const vector<SpinInteractionEdge>& intrabath_edges,
      const double pairing_cutoff);
  SpinBath(const CrystalStructure& crystal_structure,
      const auto_ptr<SpinSystemBase>& spin_system_base,
      const SpinInteractionEdge& intrabath_edge,
      const double pairing_cutoff);
  
  // Gets the state of the spin system.
  // Index is for populated sites in the crystal structure
  // Infinite temperature ensemble ...
  const SpinState& get_state(const UInt index) const;
  
  double get_pairing_cutoff() const;
  
  UInt num_spin_systems() const;
  
  // tensor product state for multiple populated sites
  SpinState get_state(const UIntArray& indices) const;
  
  const CrystalStructure& get_crystal_structure() const;
  
  const vector<SpinInteractionEdge>& get_intrabath_edges() const;
  
  const SpinSystem& get_spin_system() const;
  
  SpinInteractionGraph reduced_problem_graph(const UInt order) const;
  
  ThreeVector get_position(const UInt vertex_label,
      const UInt index) const;
  
};

} // namespace SpinDec

#endif // SPINBATH_H_
