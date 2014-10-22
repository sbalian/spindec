// See CSDProblem.h for description.
// Seto Balian, Oct 20, 2014

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
  
  central_spin_system_ = central_spin_system_base->clone();
  
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
      spin_bath_.get_spin_system()->get_hamiltonian().
      get_graph().num_vertices();
  
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

SpinSystem
CSDProblem::construct_reduced_problem(const UInt order) const
{
    
  // graphs
  
  SpinInteractionGraph bath_graph =
      spin_bath_.reduced_problem_graph(order);
  
  SpinInteractionGraph system_graph =
      central_spin_system_->get_hamiltonian().get_graph();
  
  SpinInteractionGraph system_bath_graph =
      system_graph.join(bath_graph);
  
  system_bath_graph.add_edges(make_system_bath_edges(order));
  
  
  return SpinSystem( SpinHamiltonian(system_bath_graph,field_) );
  
}

const SpinBath& CSDProblem::get_spin_bath() const
{
  return spin_bath_;
}

CSDProblem::CSDProblem(const CSDProblem& csd_problem)
{
  *this = csd_problem;
}

CSDProblem& CSDProblem::operator =(const CSDProblem& csd_problem)
{

  central_spin_system_ = csd_problem.central_spin_system_->clone();
  spin_bath_ = csd_problem.spin_bath_;
  field_ = csd_problem.field_;
  system_bath_edges_ = csd_problem.system_bath_edges_;
  reduced_problems_ = csd_problem.reduced_problems_;
  return *this;

}

void CSDProblem::set_central_spin_state(const SpinState& spin_state) const
{
  central_spin_system_->set_state(spin_state);
}

auto_ptr<SpinSystemBase> CSDProblem::get_central_spin_system() const
{
  return central_spin_system_->clone();
}

SpinSystem CSDProblem::get_reduced_problem(
    const UIntArray bath_indices)
{

  const UInt order = bath_indices.size();
  if (order == 0) {
    Errors::quit("Order must be +ve non-zero integer.");
  }
  
  SpinSystem spin_system;
  
  UInt index = 0;
  bool found = false;
  
  for (UInt i =0;i<reduced_problems_.size();i++) {
    if ( reduced_problems_[i].first == order ) {
      found = true;
      index = i;
    }
  }

  if (found == true) {
    spin_system = reduced_problems_[index].second;
  } else {
    spin_system = construct_reduced_problem(order);
    reduced_problems_.push_back(
        pair< UInt,SpinSystem>(order,spin_system) );
  }
  
  // need to update the bath positions
  
  // get the site vectors
  vector<ThreeVector> bath_positions;
  for (UInt i=0;i<order;i++) {
    bath_positions.push_back(
     get_spin_bath().get_crystal_structure().get_site_vector(bath_indices[i]));
  }
    
  // get the bath vertex labels
  UIntArray bath_vertex_labels =
      get_bath_vertex_labels(order);
  
  // new positions
  vector<ThreeVector> positions;
  for (UInt i=0;i<order;i++) {
      for (UInt j=0;j<bath_vertex_labels.size()/order;j++) {
        positions.push_back(bath_positions[i]);
      }
  }
   
  for (UInt i=0;i<bath_vertex_labels.size();i++) {
    bath_vertex_labels[i] -= 
        get_central_spin_system()->get_hamiltonian().get_graph().num_vertices();
  }
  
  for (UInt i=0;i<bath_vertex_labels.size();i++) {
    positions[i]+=
     get_spin_bath().reduced_problem_graph(order).get_position(
         bath_vertex_labels[i]);
  }
  
  for (UInt i=0;i<bath_vertex_labels.size();i++) {
    bath_vertex_labels[i] += 
        get_central_spin_system()->get_hamiltonian().
        get_graph().num_vertices();
  }
  
  spin_system.update_positions(bath_vertex_labels,positions);
  
  // set the initial state
  // TODO this needs checking ...
  spin_system.set_state(get_central_spin_system()->get_state()
      ^get_spin_bath().get_bath_product_state(bath_indices));
  
  // TODO all this needs thorough checking ...
  return spin_system;
  
}

UIntArray CSDProblem::get_bath_vertex_labels(const UInt order) const
{
  
  UIntArray labels;
  const UInt n_b = 
      spin_bath_.get_spin_system()->get_hamiltonian()
      .get_graph().num_vertices();
  const UInt n_c = 
      central_spin_system_->get_hamiltonian().
      get_graph().num_vertices();
  
  for (UInt i=n_c;i<=(n_c + order*n_b - 1);i++) {
    labels.push_back(i);
  }
  
  return labels;
  
}


} // namespace SpinDec

