// See SpinDonor.h for description.
// Seto Balian, May 29, 2014

// TODO Be careful when comparing doubles ...
// TODO Tested truncated bases, OK ... but may still need some improvement

#include "SpinDec/SpinDonor.h"
#include "SpinDec/Errors.h"

#include <cmath>
#include <algorithm>
#include <utility>

namespace SpinDec
{

void SpinDonor::sort_level_labels()
{
  std::sort (level_labels_.begin(),
      level_labels_.end()); // TODO is this working OK?
  return;
}

void SpinDonor::check_level_label(const UInt level_label) const
{
  // check if input level exists in level_labels_.
  for (UInt i = 0; i < level_labels_.size();i++) {
    if (level_label == level_labels_[i]) {
      // found, all ok
      return;
    }
  }
  Errors::quit("Invalid donor level. Try using the complete basis.");
  return;
}

void SpinDonor::calc_adiabatic_level_labels()
{
  // In order of increasing energy, these are
  // |-,M-1> , |-,M-2> , ... , |-,-M>, |-,-M+1>, ... |+,+M>
  // where M = I + S

  int M = max_quantum_number();
  
  // Fill |-,M-1> , |-,M-2> , ... , |-,-M>
  int m = M - 1;
  while (m >= -M) {
    adiabatic_level_labels_.push_back(AdiabaticLabel(Sign::Minus,m));
    m -= 1;
  }
  // Fill |-,-M+1>, ... |+,+M>
  m = -M + 1;
  while (m <= M) {
    adiabatic_level_labels_.push_back(AdiabaticLabel(Sign::Plus,m));
    m += 1;
  }
  return;
}

double SpinDonor::delta() const
{
  return
  - nuclear_parameters_.get_gyromagnetic_ratio() /
  electron_parameters_.get_gyromagnetic_ratio();
}

double SpinDonor::omega() const
{
  return electron_parameters_.get_gyromagnetic_ratio()*field_.get_magnitude();
}

double SpinDonor::scaled_omega() const
{
  return omega()/hyperfine_.get_strength();
}

double SpinDonor::D(const int quantum_number) const
{
  return static_cast<double>(quantum_number) 
      + scaled_omega()*(1.0 + delta());
}

double SpinDonor::O(const int quantum_number) const
{
  const double I = nuclear_parameters_.get_quantum_number();
  return std::sqrt( I*(I + 1.0) + 0.25 
      - std::pow(static_cast<double>(quantum_number),2) );
}

double SpinDonor::R(const int quantum_number) const
{
  return std::sqrt( std::pow(D(quantum_number),2) +
                    std::pow(O(quantum_number),2) );
}

// M rad s-1
double SpinDonor::energy(const AdiabaticLabel& adiabatic_level_label) const
{
  const double A = hyperfine_.get_strength();
  const double pm = static_cast<double>(
      adiabatic_level_label.get_sign().as_int());
  const int m = adiabatic_level_label.get_quantum_number();
  return (A/2.0)*(-0.5*(1.0 + 4.0*scaled_omega()
    *static_cast<double>(m)*delta()) + pm*R(m));
}

// TODO check if this is producing the correct states ... does the same basis
// row appear for different levels?
// TODO comment this
// TODO can make this + build_basis() faster as here, there is a repeat
// of the states involved in build_basis() ...
void SpinDonor::set_eigenstates()
{
  
  const UInt dim = dimension();
  ComplexMatrix states(dim,dim);
  
  UInt state_index = 0;
  for (UInt i=0;i<dimension();i++) {

    AdiabaticLabel adiabatic_level = int_label_to_adiabatic_label(
        level_labels_[i]);
    
    ComplexVector state(dim);
    state.setZero();
    
    // get the basis
    SpinBasis basis = build_basis(adiabatic_level);
    
    Eigen::ArrayXXd basis_as_array = basis.get_basis_as_array();
    
    state(state_index) = static_cast< CDouble >(
        a(adiabatic_level.get_quantum_number()));
    state_index += 1;

    // deal with the m != |M| case
    if (basis_as_array.rows() == 2) {
        if (adiabatic_level.get_sign().isPlus()) {
          state(state_index) = static_cast< CDouble >(
              b(adiabatic_level.get_quantum_number()));
        } else {
            state(state_index) = static_cast< CDouble >(
                -b(adiabatic_level.get_quantum_number()));
        }
        state_index += 1;
    }
    
    states.col(i) = state;
    
  }
  
  eigenstates_ = states;
  return;
    
}
void SpinDonor::set_energies()
{
  RealVector energies(dimension());
  
  for (UInt i=0;i<dimension();i++) {
    energies(i) = energy(
        int_label_to_adiabatic_label(level_labels_[i]));
  }
  energies_ = energies;
  return;
}

unsigned int SpinDonor::adiabatic_label_to_int_label(
    const AdiabaticLabel& adiabatic_level_label) const
{
  const int pm = adiabatic_level_label.get_sign().as_int();
  const int m = adiabatic_level_label.get_quantum_number();
  UInt max_n = total_multiplicity();
  
  // deal with the m = |M| cases
  if (std::abs(m) == max_quantum_number()) {
    if (pm == 1) {
      return max_n;
    } else {
        return max_n/2;
    }
  }
    
  // adiabatic_level_labels_ in increasing energy, so loop over these
  // and return loop variable when input label first matches
  // one in adiabatic_level_labels_
  for (UInt i=0;i<max_n;i++) {
    if (( adiabatic_level_labels_[i].get_sign().as_int()  == pm) &&
        ( adiabatic_level_labels_[i].get_quantum_number() == m)
       ) {
      return i;
    }
  }

  Errors::quit("Could not convert adiabatic label to integer label.");
  return 0;
  
}

AdiabaticLabel SpinDonor::int_label_to_adiabatic_label(
    const UInt level_label) const
{
  return adiabatic_level_labels_[level_label];
  
}

AdiabaticLabel SpinDonor::orthogonal_adiabatic_level_label(
    AdiabaticLabel adiabatic_level_label) const
{
  
  // Deal with the case m = |M|
  if (std::abs(adiabatic_level_label.get_quantum_number())
        == max_quantum_number()) {
    return adiabatic_level_label;
  }
  
  // Switch PLUS <-> MINUS
  if (adiabatic_level_label.get_sign().isPlus()) {
    adiabatic_level_label =
        AdiabaticLabel(Sign::Minus,adiabatic_level_label.get_quantum_number());
  } else {
    adiabatic_level_label =
        AdiabaticLabel(Sign::Plus,adiabatic_level_label.get_quantum_number());
  }
  return adiabatic_level_label;
  
}

double SpinDonor::cos_theta(const int quantum_number) const
{
  return D(quantum_number)/R(quantum_number);
}

double SpinDonor::sin_theta(const int quantum_number) const
{
  return O(quantum_number)/R(quantum_number);
}

double SpinDonor::a(const int quantum_number) const
{
  return (1.0/std::sqrt(2.0))*std::sqrt(1.0 + cos_theta(quantum_number));
}

double SpinDonor::b(const int quantum_number) const
{
  return (1.0/std::sqrt(2.0))*std::sqrt(1.0 - cos_theta(quantum_number));
}

double SpinDonor::polarization(const AdiabaticLabel& adiabatic_level_label)
const
{
  return 0.5*static_cast<double>(adiabatic_level_label.get_sign().as_int())*
      std::pow(a(adiabatic_level_label.get_quantum_number()),2.0)
    - std::pow(b(adiabatic_level_label.get_quantum_number()),2.0);
}

SpinBasis SpinDonor::build_basis(const AdiabaticLabel& level) const
{
  
  // Gives the (at most two) Zeeman basis states
  // |mS = pm 1/2, mI = m mp 1/2> and |mS = mp 1/2,mI = m pm 1/2>
  // (pm = +/-, mp = -/+)
  // where mS = pm 1/2 and mI = -I ... +I in integer steps for the energy
  // state |pm,m> =
  //         a_m |mS = pm 1/2, mI = m mp 1/2> pm b_m |mS = mp 1/2,mI = m pm 1/2>
  // For m = -M, |-,-M> = |-1/2,-I> (only one Zeeman state) (M = max(m))
  // For m = +M, |+,+M> = |+1/2,+I> (only one Zeeman state)
  // |+,-M> and |-,M> don't exist.
  // For all other |pm,m>, there are two basis states.

  Eigen::ArrayXXd basis_array;
  const int pm = level.get_sign().as_int();
  const int m =  level.get_quantum_number();

  // Deal with the m = pm M cases
  if (std::abs(m) == max_quantum_number()) {
    basis_array = Eigen::ArrayXXd(1,2);
    if (m == -max_quantum_number()) {
      basis_array(0,0) = -0.5;
      basis_array(0,1) = -static_cast<double>(max_quantum_number()) + 0.5;
    } else {
        basis_array(0,0) = 0.5;
        basis_array(0,1) = static_cast<double>(max_quantum_number()) - 0.5;
      }
  } else { // For all other cases (returning two basis states)
      basis_array = Eigen::ArrayXXd(2,2);
      if (pm == 1) {
        basis_array(0,0) = 0.5;
        basis_array(0,1) = static_cast<double>(m) - 0.5;
        basis_array(1,0) = -0.5;
        basis_array(1,1) = static_cast<double>(m) + 0.5;
      } else {
          basis_array(0,0) = -0.5;
          basis_array(0,1) = static_cast<double>(m) + 0.5;
          basis_array(1,0) = 0.5;
          basis_array(1,1) = static_cast<double>(m) - 0.5;
      }
    }
  return SpinBasis(basis_array);
}

SpinBasis SpinDonor::build_basis(const std::vector<AdiabaticLabel>&
    adiabatic_level_labels)
const
{
    
  
  // rows to build final basis array
  std::vector< std::pair<double,double> > rows;
    
  // loop over levels
  for (UInt i=0;i<adiabatic_level_labels.size();i++) {
    
    // get basis for level i
    Eigen::ArrayXXd single_level_basis =
        build_basis(adiabatic_level_labels[i]).get_basis_as_array();
                
    // loop over rows of basis for level i (this is either 1 or 2 rows),
    // adding to rows vector
    for (UInt j=0;j<single_level_basis.rows();j++) {
      
      // each row has two columns, one for the electron the other
      // for the nucleus
      std::pair<double,double> row;
      row.first  = single_level_basis(j,0);
      row.second = single_level_basis(j,1);
      
      rows.push_back(row);
    
    }
  }
  
  // Now collect saved rows into an array
  
  Eigen::ArrayXXd basis(rows.size(),2);
    
  for (unsigned int i=0;i<rows.size();i++) {
    basis(i,0) = rows[i].first;
    basis(i,1) = rows[i].second;
  }

  return SpinBasis(basis);
  
}

SpinBasis SpinDonor::build_basis(const UIntArray& level_labels) const
{
  
  // convert vector of integer labels to adiabatic labels
  std::vector<AdiabaticLabel> adiabatic_labels;
  for (unsigned int i=0;i<level_labels.size();i++) {
    adiabatic_labels.push_back(int_label_to_adiabatic_label(level_labels[i]));
  }
  return build_basis(adiabatic_labels);
  
}

SpinBasis SpinDonor::build_basis() const
{
  
  return build_basis(level_labels_);
  
}

void SpinDonor::set_transition(const UInt lower_level_label,
    const UInt upper_level_label)
{
  
  // checks
  
  if (lower_level_label > total_multiplicity()) {
    Errors::quit("Invalid label for lower energy level.");
  }
  if (upper_level_label > total_multiplicity()) {
    Errors::quit("Invalid label for upper energy level.");
  }
  if ( upper_level_label == lower_level_label ) {
    Errors::quit("Upper and lower labels for donor levels must be different.");
    return;
  }
  if ( upper_level_label < lower_level_label ) {
    Errors::quit(
    "Lower level label must be lower in value than label for upper level.");
    return;
  }
  
  lower_level_label_ = lower_level_label;
  upper_level_label_ = upper_level_label;
    
  UInt orthogonal_level_to_set = orthogonal_level_label(lower_level_label);
  if (orthogonal_level_to_set != lower_level_label) {
    orthogonal_level_labels_.push_back(orthogonal_level_to_set);
  }
  
  orthogonal_level_to_set = orthogonal_level_label(upper_level_label);
  if (orthogonal_level_to_set != upper_level_label) {
    orthogonal_level_labels_.push_back(orthogonal_level_to_set);
  }
  
  return;
  
}

UInt SpinDonor::level_label_index(const UInt level_label) const
{
  for (UInt i = 0; i < level_labels_.size();i++) {
    if (level_label == level_labels_[i]) {
      return i;
    }
  }
  Errors::quit("Invalid level label.");
  return 0;
}

UInt SpinDonor::orthogonal_level_label(const UInt level_label) const
{
  AdiabaticLabel adiabatic_label = int_label_to_adiabatic_label(level_label);
  AdiabaticLabel orthogonal_adiabatic_label =
      orthogonal_adiabatic_level_label(adiabatic_label);
  return adiabatic_label_to_int_label(orthogonal_adiabatic_label);
}


SpinDonor::SpinDonor() : SpinSystemBase(),
    complete_basis_(true),lower_level_label_(0),
    upper_level_label_(0)
{/**/}

SpinDonor::SpinDonor(const double field_strength,
    const double nuclear_quantum_number,
    const double electron_gyromagnetic_ratio,
    const double nuclear_gyromagnetic_ratio,
    const double hyperfine_strength,
    const unsigned int lower_level_label,
    const unsigned int upper_level_label,
    const ThreeVector & electron_position,
    const ThreeVector & nuclear_position,
    const bool complete_basis) : SpinSystemBase(),
        complete_basis_(complete_basis),
        hyperfine_(Hyperfine(hyperfine_strength))
{
  
  // set the rest of the data members and build spin interaction graph

  field_ = UniformMagneticField(field_strength);
  
  electron_parameters_ = ElectronSpinParameters(electron_gyromagnetic_ratio);
  nuclear_parameters_ = NuclearSpinParameters(nuclear_quantum_number,
                                              nuclear_gyromagnetic_ratio);

  calc_adiabatic_level_labels();
  
  set_transition(lower_level_label,upper_level_label);
  
  if (complete_basis_ == false) {
    level_labels_.push_back(lower_level_label);
    level_labels_.push_back(upper_level_label);
    for (UInt i=0;i<orthogonal_level_labels_.size();i++) {
      level_labels_.push_back(orthogonal_level_labels_[i]);
    }
    sort_level_labels();
  } else {
      for (UInt i = 0; i < total_multiplicity();i++) {
        level_labels_.push_back(i);
      }
  }
  
  graph_.add_vertex(electron_parameters_,electron_position);
  graph_.add_vertex(nuclear_parameters_,nuclear_position);
  graph_.add_edge(0,1,hyperfine_.clone());
  
  if (complete_basis_ == false) {
    graph_.set_basis(build_basis());
  }
  
  hamiltonian_ = SpinHamiltonian(graph_,field_);
    
  set_energies();
  set_eigenstates();
  
}

const ElectronSpinParameters& SpinDonor::get_electron_parameters() const
{
  return electron_parameters_;
}

const NuclearSpinParameters& SpinDonor::get_nuclear_parameters() const
{
  return nuclear_parameters_;
}

// TODO Check if this is OK!!!
const Hyperfine& SpinDonor::get_hyperfine() const
{
  return hyperfine_;
}

// TODO Is this safe? Checked ... OK for 0.5 + 4.5 = 5
int SpinDonor::max_quantum_number() const
{
  return static_cast<int>(electron_parameters_.get_quantum_number() +
      nuclear_parameters_.get_quantum_number());
  
}

UInt SpinDonor::dimension() const
{
  if (complete_basis_ == false) {
    return hamiltonian_.get_dimension();
  }
  return total_multiplicity();
}

UInt SpinDonor::total_multiplicity() const
{
  return electron_parameters_.get_multiplicity()
         *nuclear_parameters_.get_multiplicity();
}

SpinState SpinDonor::eigenstate(const UInt level_label) const
{
  check_level_label(level_label);
  return SpinState(eigenstates_.col(level_label_index(level_label)),
      hamiltonian_.get_basis());
}

double SpinDonor::energy(const UInt level_label) const
{
  check_level_label(level_label);
  return energies_(level_label_index(level_label));
}

double SpinDonor::polarization(const UInt level_label) const
{
  check_level_label(level_label);
  return polarization(int_label_to_adiabatic_label(level_label));
}

} // namespace SpinDec

