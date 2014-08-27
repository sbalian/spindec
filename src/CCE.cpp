// See CCE.h for description.
// Seto Balian, Aug 27, 2014

#include "SpinDec/CCE.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

void CCE::init(const UInt truncation_order,
    const auto_ptr<SpinSystemBase>& central_spin_system_base,
    const SpinBath& spin_bath,
    const vector<SpinInteractionEdge>& system_bath_edges,
    const UniformMagneticField& field)
{
  
  // Truncation order
  
  truncation_order_ = truncation_order;
  if (truncation_order == 0) {
    Errors::quit("CCE truncation order must be +ve non-zero integer");
  }
  
  // Central spin system
  
  // TODO again, rediagonalization ...
  central_spin_system_ = SpinSystem(central_spin_system_base->get_graph(),
      central_spin_system_base->get_field());
  
  // Spin bath
  spin_bath_ = spin_bath;
  
  // Field
  field_ = field;
  
  // System-bath interaction
  system_bath_edges_ = system_bath_edges;
  
  // Prepare the reduced problems ...
  
  // truncation order 3
  // bath graph = 1-cluster graph
  // 1-cluster
  // graph = 1c
  // 2-cluster
  // edge indices intact
  // graph = 1c+1c
  // 3-cluster
  // edge indices + 
  // graph = 1c+1c+1c
  
  // Start with bath graphs
//  for (UInt i=1;i<=truncation_order_;i++) {
//    SpinInteractionGraph bath_graph =
//        spin_bath_.get_spin_system().get_graph();
//    
//    
//    
//    for (UInt j=0;j<i;j++) {
//      graph.join_in_place(spin_bath_.get_spin_system().get_graph(),
//              system_bath_edges_);
//    }
//  }
//  
//  for (UInt i=1;i<=truncation_order_;i++) {
//    
//    SpinInteractionGraph graph =
//        central_spin_system_.get_graph();
//    
//    for (UInt j=0;j<i;j++) {
//      graph.join_in_place(spin_bath_.get_spin_system().get_graph(),
//              system_bath_edges_);
//    }
//    
//    reduced_problems_.pus
//    
//  }
//  
//
  
  return;
  
}


CCE::CCE() : truncation_order_(0)
{
}


CCE::CCE(const UInt truncation_order,
    const auto_ptr<SpinSystemBase>& central_spin_system_base,
    const SpinBath& spin_bath,
    const vector<SpinInteractionEdge>& system_bath_edges,
    const UniformMagneticField& field)
{
  init(truncation_order,
    central_spin_system_base,
    spin_bath,
    system_bath_edges,
    field);
}

CCE::CCE(const UInt truncation_order,
    const auto_ptr<SpinSystemBase>& central_spin_system_base,
    const SpinBath& spin_bath, const SpinInteractionEdge& system_bath_edge,
    const UniformMagneticField& field)
{
  vector<SpinInteractionEdge> system_bath_edges;
  system_bath_edges.push_back(system_bath_edge);
  init(truncation_order,
    central_spin_system_base,
    spin_bath,
    system_bath_edges,
    field);
}

} // namespace SpinDec
