// See SpinSystem.h for description.
// Seto Balian, Sep 11, 2014

#include "SpinDec/SpinSystem.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

void SpinSystem::diagonalize()
{
  eigenspectrum_ = HermitianEigenspectrum(hamiltonian_.get_matrix());
  return;
}

void SpinSystem::set_eigenstates()
{
  // just sets, already calculated in constructor
  eigenstates_ = eigenspectrum_.get_eigenvectors();
  return;
}

void SpinSystem::set_energies()
{
  // just sets, already calculated in constructor
  energies_ = eigenspectrum_.get_eigenvalues().real();
  return;
}

SpinSystem::SpinSystem() : SpinSystemBase()
{
}

void SpinSystem::check_level_label(const UInt level_label) const
{
  if (level_label < dimension()) {
    return; // all ok
  } // else
    Errors::quit("Energy levels: 0,1,2,...,dim(Hamiltonian)");
    return;
}

SpinSystem::SpinSystem(const SpinInteractionGraph & graph,
    const UniformMagneticField & field) :
    SpinSystemBase(graph,field)
{
  diagonalize();
  set_energies();
  set_eigenstates();
}

UInt SpinSystem::dimension() const
{
  return hamiltonian_.get_dimension();
}

auto_ptr<SpinSystemBase> SpinSystem::clone() const
{
  return auto_ptr<SpinSystemBase> (new SpinSystem(*this));
}

//void SpinSystem::update_positions(const UIntArray& vertex_labels,
//    const vector<ThreeVector>& positions)
//{
//  
//  if (vertex_labels.size() != positions.size()) {
//    Errors::quit("Vertex label and position arrays must be of the same size.");
//    return;
//  }
//  
//  hamiltonian_.update_positions(vertex_labels,positions);
//  
//  for (UInt l=0;l<vertex_labels.size();l++) {
//    graph_.set_position(l,positions[l]);
//  }
//  
//  diagonalize();
//  set_energies();
//  set_eigenstates();
//  
//  return;
//  
//}

} // namespace SpinDec

