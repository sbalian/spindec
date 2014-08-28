// See CCE.h for description.
// Seto Balian, Aug 28, 2014

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
  
    
  for (UInt i=1;i<=truncation_order_;i++) {
    
    // graphs
    
    SpinInteractionGraph bath_graph =
        spin_bath_.reduced_problem_graph(i);
    
    SpinInteractionGraph system_graph =
        central_spin_system_.get_graph();
    
    SpinInteractionGraph system_bath_graph =
        system_graph.join(bath_graph);
    
    system_bath_graph.add_edges(get_system_bath_edges(i));
    
    // spin systems
    
    reduced_problems_.push_back(SpinSystem(system_bath_graph,field_));
    
  }
  
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

vector<SpinInteractionEdge> CCE::get_system_bath_edges(const UInt order,
  const SpinInteractionEdge& edge) const
{
  
  if (order == 0) {
    Errors::quit("Order must be +ve non-zero integer.");
  }
  
  const UInt a = edge.get_label1();
  const UInt b = edge.get_label2();
  
  vector<SpinInteractionEdge> edges;
  
  vector< std::pair<UInt,UInt> > pairs;
  
  const UInt num_vertices =
      spin_bath_.get_spin_system().get_graph().num_vertices();
  
  for (UInt i=1;i<=order;i++) {
    pairs.push_back(std::pair<UInt,UInt>( a , b + (i-1)*num_vertices ));
  }
  
  for (UInt i=0;i<pairs.size();i++) {
    edges.push_back( SpinInteractionEdge(
        pairs[i].first ,pairs[i].second ,edge.get_interaction()) );
  }
  
  return edges;
  
}

vector<SpinInteractionEdge> CCE::get_system_bath_edges(const UInt order) const
{
  
    vector<SpinInteractionEdge> edges;
    
    for (UInt i=0;i<system_bath_edges_.size();i++) {
      vector<SpinInteractionEdge> edges_i = get_system_bath_edges(order,
          system_bath_edges_[i]);
      
      for (UInt j=0;j<edges_i.size();j++) {
        edges.push_back(edges_i[j]);
      }
      
    }
    
    return edges;
  
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

const SpinSystem& CCE::get_reduced_problem(const UInt order) const
{
  
  if (order == 0) {
    Errors::quit("Order must be +ve non-zero integer.");
  }
  
  if (order > truncation_order_) {
    Errors::quit("Order must be less than or equal to truncation order");
  }
  
  return reduced_problems_[order-1];

}

} // namespace SpinDec
