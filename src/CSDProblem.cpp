// See CSDProblem.h for description.
// Seto Balian, Sep 1, 2014

#include "SpinDec/CSDProblem.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

void CSDProblem::init(
    const auto_ptr<SpinSystemBase>& central_spin_system_base,
    const SpinBath& spin_bath,
    const vector<SpinInteractionEdge>& system_bath_edges,
    const UniformMagneticField& field)
{
  
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
  
  return;
  
}

vector<SpinInteractionEdge> CSDProblem::make_system_bath_edges(
    const UInt order, const SpinInteractionEdge& edge) const
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

vector<SpinInteractionEdge> CSDProblem::make_system_bath_edges(
    const UInt order) const
{
  
  vector<SpinInteractionEdge> edges;
  
  for (UInt i=0;i<system_bath_edges_.size();i++) {
    vector<SpinInteractionEdge> edges_i = make_system_bath_edges(order,
        system_bath_edges_[i]);
    
    for (UInt j=0;j<edges_i.size();j++) {
      edges.push_back(edges_i[j]);
    }
    
  }
  
  return edges;

}

CSDProblem::CSDProblem()
{
}

CSDProblem::CSDProblem(
    const auto_ptr<SpinSystemBase>& central_spin_system_base,
    const SpinBath& spin_bath,
    const vector<SpinInteractionEdge>& system_bath_edges,
    const UniformMagneticField& field)
{
  init(central_spin_system_base,
    spin_bath,
    system_bath_edges,
    field);

}

CSDProblem::CSDProblem(
    const auto_ptr<SpinSystemBase>& central_spin_system_base,
    const SpinBath& spin_bath, const SpinInteractionEdge& system_bath_edge,
    const UniformMagneticField& field)
{
  
  vector<SpinInteractionEdge> system_bath_edges;
  system_bath_edges.push_back(system_bath_edge);
  init(central_spin_system_base,
    spin_bath,
    system_bath_edges,
    field);
  
}

SpinSystem CSDProblem::reduced_problem(const UInt order) const
{
  
  if (order == 0) {
    Errors::quit("Order must be +ve non-zero integer.");
  }
  
    
  // graphs
  
  SpinInteractionGraph bath_graph =
      spin_bath_.reduced_problem_graph(order);
  
  SpinInteractionGraph system_graph =
      central_spin_system_.get_graph();
  
  SpinInteractionGraph system_bath_graph =
      system_graph.join(bath_graph);
  
  system_bath_graph.add_edges(make_system_bath_edges(order));
  
  // spin systems
  
  return SpinSystem(system_bath_graph,field_);
    
  
}

const SpinBath& CSDProblem::get_spin_bath() const
{
  return spin_bath_;
}

const SpinSystem& CSDProblem::get_central_spin_system() const
{
  return central_spin_system_;
}

UIntArray CSDProblem::get_bath_vertex_labels(const UInt order) const
{
  
  UIntArray labels;
  const UInt n_b = 
      spin_bath_.get_spin_system().get_graph().num_vertices();
  const UInt n_c = 
      central_spin_system_.get_graph().num_vertices();
  
  for (UInt i=n_c;i<=(n_c + order*n_b - 1);i++) {
    labels.push_back(i);
  }
  
  return labels;
  
}


} // namespace SpinDec

