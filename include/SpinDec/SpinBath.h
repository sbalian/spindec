#ifndef SPINBATH_H_
#define SPINBATH_H_

// Seto Balian, Jul 22, 2015

// TODO gereneralize (1) heteronuclear (2) finite temperature

#include "SpinDec/typedefs.h"

#include "SpinDec/CrystalStructure.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/SpinInteractionEdge.h"

namespace SpinDec
{

/**
 * \brief Spin bath (single spin species).
 * 
 * For the central spin decoherence problem in a crystal. Infinite temperature,
 * so that all states are equally likely.
 * 
 */
class SpinBath
{
private:
  
  vector<SpinState> bath_states_;
  CrystalStructure crystal_structure_;
  
  /**
   * This spin system is placed at every occupied site in the crystal
   * structure. The positions of each of the spins in the spin systems are
   * added to the site vector.
   */
  shared_ptr<SpinSystemBase> spin_system_base_;
  
  /**
   * Take the graph of the spin system and consider joining the graph to itself.
   * For example, if the vertices of the original graph were 0, 1, 2,
   * the new graph will have vertices 0, 1, 2 (originals), 3, 4, 5 (copies).
   * Use these new labels for the intrabath edges.
   * This is like the joining methods in SpinInteractionGraph.
   */
  vector<SpinInteractionEdge> intrabath_edges_;
  
  void init(const CrystalStructure& crystal_structure,
      const shared_ptr<SpinSystemBase>& spin_system_base,
      const vector<SpinInteractionEdge>& intrabath_edges,const UInt seed);
  
  vector<SpinInteractionEdge> make_intrabath_edges(const UInt order,
      const SpinInteractionEdge& intrabath_edge) const;
  vector<SpinInteractionEdge> make_intrabath_edges(const UInt order) const;
  
  
public:
  SpinBath();
  
  SpinBath(const CrystalStructure& crystal_structure,
      const shared_ptr<SpinSystemBase>& spin_system_base,
      const vector<SpinInteractionEdge>& intrabath_edges,
      const UInt seed);
  
  SpinBath(const CrystalStructure& crystal_structure,
      const shared_ptr<SpinSystemBase>& spin_system_base,
      const SpinInteractionEdge& intrabath_edge,
      const UInt seed);
  
  SpinBath(const SpinBath& spin_bath);

  SpinBath& operator=(const SpinBath& spin_bath);

  /**
   * \brief Gets the state of the spin system.
   * 
   * Index is for populated sites in the crystal structure.
   * Infinite temperature ensemble ...
   */
  const SpinState& get_bath_state(const UInt index) const;
  
  UInt num_bath_states() const;
  
  /// Tensor product state for multiple populated sites.
  SpinState get_bath_product_state(const UIntArray& indices) const;
  
  const CrystalStructure& get_crystal_structure() const;
  
  const vector<SpinInteractionEdge>& get_intrabath_edges() const;
  
  shared_ptr<SpinSystemBase> get_spin_system() const;
  
  SpinInteractionGraph reduced_problem_graph(const UInt order) const;
  
  ThreeVector get_position(const UInt vertex_label,
      const UInt bath_index) const;
  
  void set_bath_state(const UInt index, const UInt level);
  
};

} // namespace SpinDec

#endif // SPINBATH_H_
