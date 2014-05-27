// See SpinDonor.h for description.
// Seto Balian, May 27, 2014

// TODO Be careful when comparing doubles ...
// TODO Tested truncated bases, OK ... but may still need some improvement

#include "SpinDec/SpinDonor.h"
#include "SpinDec/Errors.h"

#include <cmath>
#include <algorithm>
#include <utility>

namespace SpinDec
{

void SpinDonor::check_level(const UInt level) const
{
  if (level < 1) {
    Errors::quit("Donor level must be 1,2,...,dimension(donor).");
    return;
  }
  if (level > total_multiplicity()) {
    Errors::quit("Donor level must be 1,2,...,dimension(donor).");
  }
  return;
}


void SpinDonor::calc_energy_levels()
{
  // In order of increasing energy, these are
  // |-,M-1> , |-,M-2> , ... , |-,-M>, |-,-M+1>, ... |+,+M>
  // where M = I + S

  int M = max_quantum_number();
  
  // Fill |-,M-1> , |-,M-2> , ... , |-,-M>
  int m = M - 1;
  while (m >= -M) {
    energy_levels_.push_back(AdiabaticLabel(Sign::Minus,m));
    m -= 1;
  }
  // Fill |-,-M+1>, ... |+,+M>
  m = -M + 1;
  while (m <= M) {
    energy_levels_.push_back(AdiabaticLabel(Sign::Plus,m));
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
double SpinDonor::energy(const AdiabaticLabel& label) const
{
  const double A = hyperfine_.get_strength();
  const double pm = static_cast<double>(label.get_sign().as_int());
  const int m = label.get_quantum_number();
  return (A/2.0)*(-0.5*(1.0 + 4.0*scaled_omega()
    *static_cast<double>(m)*delta()) + pm*R(m));
}

Eigen::VectorXd SpinDonor::energies() const
{
  Eigen::VectorXd eigenvalues(dimension());
  
  if (complete_basis_ == true) {
    for (UInt i=1 ; i<=total_multiplicity(); i++ ) {
      eigenvalues(i-1) = energy(int_label_to_adiabatic_label(i));
    }
  } else {
      eigenvalues
  }
}

ComplexMatrix SpinDonor::eigenstates() const
{
  
}

unsigned int SpinDonor::adiabatic_label_to_int_label(
    const AdiabaticLabel& label) const
{
  const int pm = label.get_sign().as_int();
  const int m = label.get_quantum_number();
  UInt max_n = total_multiplicity();
  
  // deal with the m = |M| cases
  if (std::abs(m) == max_quantum_number()) {
    if (pm == 1) {
      return max_n;
    } else {
        return max_n/2;
    }
  }
  
  if (energy_levels_.size() == 0) {
    Errors::quit("Need to set adiabatic levels first.");
  }
  
  // energy_levels_ in increasing energy, so loop over these
  // and return loop variable when input label first matches
  // one in energy_levels_
  for (UInt i=0;i<max_n;i++) {
    if (( energy_levels_[i].get_sign().as_int()  == pm) &&
        ( energy_levels_[i].get_quantum_number() == m)
       ) {
      return i+1;
    }
  }

  Errors::quit("Could not convert adiabatic label to integer label.");
  return 0;
  
}

AdiabaticLabel SpinDonor::int_label_to_adiabatic_label(const UInt level) const
{
  
  check_level(level);
  
  if (energy_levels_.size() == 0) {
    Errors::quit("Need to set adiabatic levels first.");
  }
  
  return energy_levels_[level-1];
  
}

AdiabaticLabel SpinDonor::orthogonal_level(AdiabaticLabel level) const
{
  
  // Deal with the case m = |M|
  if (std::abs(level.get_quantum_number()) == max_quantum_number()) {
    return level;
  }
  
  // Switch PLUS <-> MINUS
  if (level.get_sign().isPlus()) {
    level = AdiabaticLabel(Sign::Minus,level.get_quantum_number());
  } else {
      level = AdiabaticLabel(Sign::Plus,level.get_quantum_number());
  }
  return level;
  
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

double SpinDonor::polarization(const AdiabaticLabel& level) const
{
  return 0.5*static_cast<double>(level.get_sign().as_int())*
      std::pow(a(level.get_quantum_number()),2.0)
    - std::pow(b(level.get_quantum_number()),2.0);
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

SpinBasis SpinDonor::build_basis(const std::vector<AdiabaticLabel>& levels)
const
{
    
  
  // rows to build final basis array
  std::vector< std::pair<double,double> > rows;
    
  // loop over levels
  for (UInt i=0;i<levels.size();i++) {
    
    // get basis for level i
    Eigen::ArrayXXd single_level_basis =
        build_basis(levels[i]).get_basis_as_array();
                
    // loop over rows of basis for level i (this is either 1 or 2 rows),
    // adding to rows vector
    for (UInt j=0;j<single_level_basis.rows();j++) {
      
      // each row has two columns, one for the electron the other
      // for the nucleus
      std::pair<double,double> row;
      row.first  = single_level_basis(j,0);
      row.second = single_level_basis(j,1);
      
      rows.push_back(row);

      // TODO NOT REQUIRED (see build_truncated_basis method)
      // code to avoid duplicate entries
//      // always add the first basis (no duplicate entries)
//      if (i == 0) {
//        rows.push_back(row);
//        continue;
//      }
//      
//      bool add_row = true;
//      for (UInt k = 0; k< rows.size();k++) {
//        if ((rows[k].first == row.first) && (rows[k].second == row.second)) {
//          // duplicate found
//          add_row = false;
//          break;
//        }
//      }
//      
//      if (add_row == true) {
//        rows.push_back(row);
//      }
    
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

SpinBasis SpinDonor::build_basis(const UIntArray& levels) const
{
  
  // convert vector of integer labels to adiabatic labels
  std::vector<AdiabaticLabel> adiabatic_labels;
  for (unsigned int i=0;i<levels.size();i++) {
    adiabatic_labels.push_back(int_label_to_adiabatic_label(levels[i]));
  }
  return build_basis(adiabatic_labels);
  
}


SpinBasis SpinDonor::build_truncated_basis() const
{
  UIntArray levels;
  levels.push_back(upper_energy_level_);
  levels.push_back(lower_energy_level_);
  // TODO NOT REQUIRED (see build_basis method for multiple adiabatic levels)
//  levels.push_back(orthogonal_upper_energy_level_);
//  levels.push_back(orthogonal_lower_energy_level_);
  return build_basis(levels);
  
}

void SpinDonor::set_transition(const UInt upper_energy_level,
    const UInt lower_energy_level)
{
  // check if levels valid
  
  check_level(upper_energy_level);
  check_level(lower_energy_level);
  
  if ( upper_energy_level == lower_energy_level ) {
    Errors::quit("Upper and lower donor levels must be different.");
    return;
  }
  
  if ( upper_energy_level < lower_energy_level ) {
    Errors::quit("Lower donor level must be smaller in value than upper.");
    return;
  }
  
  upper_energy_level_ = upper_energy_level;
  lower_energy_level_ = lower_energy_level;
  
  orthogonal_upper_energy_level_ = orthogonal_level(upper_energy_level);
  orthogonal_lower_energy_level_ = orthogonal_level(lower_energy_level);
  return;
  
}

SpinDonor::SpinDonor() : upper_energy_level_(0),lower_energy_level_(0),
    orthogonal_upper_energy_level_(0),orthogonal_lower_energy_level_(0),
    complete_basis_(true)
{/**/}

SpinDonor::SpinDonor(const double field_strength,
    const double nuclear_quantum_number,
    const double electron_gyromagnetic_ratio,
    const double nuclear_gyromagnetic_ratio,
    const double hyperfine_strength,
    const unsigned int upper_energy_level,
    const unsigned int lower_energy_level,
    const ThreeVector & electron_position,
    const ThreeVector & nuclear_position,
    const bool complete_basis) :
        hyperfine_(Hyperfine(hyperfine_strength)),
        upper_energy_level_(upper_energy_level),
        lower_energy_level_(lower_energy_level),
        orthogonal_upper_energy_level_(0),
        orthogonal_lower_energy_level_(0),
        complete_basis_(complete_basis)
{
  
  // set the rest of the data members and build spin interaction graph

  field_ = UniformMagneticField(field_strength);
  
  electron_parameters_ = ElectronSpinParameters(electron_gyromagnetic_ratio);
  nuclear_parameters_ = NuclearSpinParameters(nuclear_quantum_number,
                                              nuclear_gyromagnetic_ratio);

  calc_energy_levels();
  
  set_transition(upper_energy_level,lower_energy_level);
  
  graph_.add_vertex(electron_parameters_,electron_position);
  graph_.add_vertex(nuclear_parameters_,nuclear_position);
  graph_.add_edge(0,1,hyperfine_.clone());
  
  if (complete_basis_ == false) {
    graph_.set_basis(build_truncated_basis());
  }
  
  hamiltonian_ = SpinHamiltonian(graph_,field_);
  eigenspectrum_ = HermitianEigenspectrum(eigenstates(),energies());
  
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

double SpinDonor::polarization(const UInt level) const
{
  return polarization(int_label_to_adiabatic_label(level));
}

UInt SpinDonor::orthogonal_level(const UInt level) const
{
  AdiabaticLabel adiabatic_label = int_label_to_adiabatic_label(level);
  AdiabaticLabel orthogonal_adiabatic_label = orthogonal_level(adiabatic_label);
  return adiabatic_label_to_int_label(orthogonal_adiabatic_label);
}

} // namespace SpinDec

