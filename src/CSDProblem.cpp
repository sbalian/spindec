// See CSDProblem.h for description.
// Seto Balian, Sep 3, 2014

#include "SpinDec/CSDProblem.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

void CSDProblem::init(
    const auto_ptr<SpinSystemBase>& central_spin_system_base,
    const SpinBath& spin_bath,
    const vector<SpinInteractionEdge>& system_bath_edges,
    const UniformMagneticField& field,
    const auto_ptr<PulseExperiment> & pulse_experiment)
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
  
  // Pulse experiment
  pulse_experiment_ = pulse_experiment->clone();
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
    const UniformMagneticField& field,
    const auto_ptr<PulseExperiment> & pulse_experiment)
{
  init(central_spin_system_base,
    spin_bath,
    system_bath_edges,
    field,pulse_experiment);

}

CSDProblem::CSDProblem(
    const auto_ptr<SpinSystemBase>& central_spin_system_base,
    const SpinBath& spin_bath, const SpinInteractionEdge& system_bath_edge,
    const UniformMagneticField& field,
    const auto_ptr<PulseExperiment> & pulse_experiment)
{
  
  vector<SpinInteractionEdge> system_bath_edges;
  system_bath_edges.push_back(system_bath_edge);
  init(central_spin_system_base,
    spin_bath,
    system_bath_edges,
    field,pulse_experiment);
  
}

SpinSystem CSDProblem::construct_reduced_problem(const UInt order) const
{
  
    
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
    }
  }
  
  if (found == true) {
    spin_system = reduced_problems_[index].second;
  } else {
    spin_system = construct_reduced_problem(order);
    reduced_problems_.push_back( pair< UInt,SpinSystem>(order,spin_system) );
  }
  
  // now set the initial bath positions
  
  // get the site vectors
  vector<ThreeVector> sites;
  for (UInt i=0;i<order;i++) {
    sites.push_back(
     get_spin_bath().get_crystal_structure().get_site_vector(bath_indices[i]));
  }
  
  // get the bath vertex labels
  UIntArray bath_vertex_labels =
      get_bath_vertex_labels(order);
  // get the number of bath vertices
  UInt num_bath_vertices =
      get_spin_bath().get_spin_system().get_graph().num_vertices();
  
  // new positions
  vector<ThreeVector> positions;
  for (UInt i=0;i<order;i++) {
    for (UInt j=0;j<num_bath_vertices;j++) {
      positions.push_back(sites[i]);
    }
  }
  for (UInt i=0;i<bath_vertex_labels.size();i++) {
    positions[i]+=
     get_spin_bath().get_spin_system().get_graph().get_position(i);
  }
  spin_system.update_positions(bath_vertex_labels,positions);

  // set the initial state
  // TODO this needs checking ...
  spin_system.set_state(get_central_spin_system().get_state()
      ^get_spin_bath().get_state(bath_indices));
  
  // TODO all this needs thorough checking ...
  return spin_system;
  
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

TimeEvolution CSDProblem::time_evolution(const SpinSystem& reduced_problem)
{
  return pulse_experiment_->time_evolution(reduced_problem.get_state());
}

CSDProblem& CSDProblem::operator =(const CSDProblem& other)
{
   central_spin_system_=other.central_spin_system_;
   spin_bath_=other.spin_bath_;
   field_=other.field_;
   pulse_experiment_= other.pulse_experiment_->clone();
   system_bath_edges_=other.system_bath_edges_;
   reduced_problems_=other.reduced_problems_;
   return *this;
}

SpinDec::CSDProblem::CSDProblem(const CSDProblem& other)
{
  *this = other;
}

auto_ptr<PulseExperiment> CSDProblem::get_pulse_experiment() const
{
  return pulse_experiment_->clone();
}


} // namespace SpinDec

