// See SpinDonor.h for description.
// Seto Balian, May 16, 2014

#include "SpinDec/SpinDonor.h"
#include "SpinDec/Errors.h"
#include <cmath>

namespace SpinDec
{

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
double SpinDonor::eigenvalue(const AdiabaticLabel& label) const
{
  const double A = hyperfine_.get_strength();
  const double pm = static_cast<double>(label.get_sign().as_int());
  const int m = label.get_quantum_number();
  return (A/2.0)*(-0.5*(1.0 + 4.0*scaled_omega()
    *static_cast<double>(m)*delta()) + pm*R(m));
}

unsigned int SpinDonor::adiabatic_label_to_int_label(
    const AdiabaticLabel& label) const
{
  const int pm = label.get_sign().as_int();
  const int m = label.get_quantum_number();
  UInt max_n = dimension();
  
  // energy_level_labels_ in increasing energy, so loop over these
  // and return loop variable when input label first matches
  // one in energy_level_labels_
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

AdiabaticLabel SpinDonor::orthogonal_level(AdiabaticLabel level) const
{
  // Deal with the case m = |M|
  if (level.get_quantum_number() == std::abs(max_quantum_number())) {
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
  
  // code avoids duplicate basis rows/entries
  
  // rows to build final basis array
  std::vector<Eigen::ArrayXd> rows;
    
  // loop over levels
  for (UInt i=0;i<levels.size();i++) {
    
    // get basis for level i
    Eigen::ArrayXXd single_level_basis =
        build_basis(levels[i]).get_basis_as_array();
        
    // loop over rows of basis for level i (this is either 1 or 2 rows)
    for (UInt j=0;j<single_level_basis.rows();j++) {
      
      // TODO BUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUG!!!
      
      // loop over saved rows
      for (unsigned int k=0;k<rows.size();k++) {
        // if row exists in saved rows
        if ((rows[k](0) == single_level_basis(j,0) ) &&
            (rows[k](1) == single_level_basis(j,1) ) ){
          break; // do not add it and move on to the next row
        } else { // if row does not exist, add it to saved rows
            Eigen::ArrayXd row(2);
            // each row has two columns, one for the electron the other
            // for the nucleus
            row(0) = single_level_basis(j,0);
            row(1) = single_level_basis(j,1);
            rows.push_back(row);
        }
      }
    }
    
  }
    
  // Now collect saved rows into an array
  
  // number of rows
  int num_rows = 0;
  for (UInt i=0;i<rows.size();i++) {
    num_rows += 1;
  }

  Eigen::ArrayXXd basis(num_rows,2);
    
  for (unsigned int i=0;i<rows.size();i++) {
    basis(i,0) = rows[i](0);
    basis(i,1) = rows[i](1);
  }

  return SpinBasis(basis);
  
}

SpinBasis SpinDonor::build_basis(const UIntArray& levels) const
{
  // convert vector of integer labels to adiabatic labels
  std::vector<AdiabaticLabel> adiabatic_labels;
  for (unsigned int i=0;i<levels.size();i++) {
    adiabatic_labels.push_back(energy_levels_[levels[i]]);
  }
  return build_basis(adiabatic_labels);
}


SpinBasis SpinDonor::build_truncated_basis() const
{
  UIntArray levels;
  levels.push_back(upper_energy_level_);
  levels.push_back(lower_energy_level_);
  levels.push_back(orthogonal_upper_energy_level_);
  levels.push_back(orthogonal_lower_energy_level_);
  return build_basis(levels);
}

void SpinDonor::set_transition(const UInt upper_energy_level,
    const UInt lower_energy_level)
{
  // check if levels valid
  
  if ( !(upper_energy_level < dimension()) ) {
    Errors::quit("Upper donor level must be 1,2,...,dimension(donor).");
    return;
  }
  
  if ( !(lower_energy_level < dimension()) ) {
    Errors::quit("Lower donor level must be 1,2,...,dimension(donor).");
    return;
  }
  
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
    orthogonal_upper_energy_level_(0),orthogonal_lower_energy_level_(0)
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
        upper_energy_level_(0),
        lower_energy_level_(0),
        orthogonal_upper_energy_level_(0),
        orthogonal_lower_energy_level_(0)
{
  
  
  // set the rest of the data members and build spin interaction graph

  field_ = UniformMagneticField(field_strength);
  
  electron_parameters_ = ElectronSpinParameters(electron_gyromagnetic_ratio);
  nuclear_parameters_ = NuclearSpinParameters(nuclear_quantum_number,
                                              nuclear_gyromagnetic_ratio);

  calc_energy_levels();

  add_vertex(electron_parameters_,electron_position);
  add_vertex(nuclear_parameters_,nuclear_position);
  add_edge(0,1,hyperfine_.clone());
  
  if (complete_basis == false) {
    set_basis(build_truncated_basis());
  }
  
  set_transition(upper_energy_level,lower_energy_level);
  
}

const UniformMagneticField& SpinDonor::get_field() const
{
  return field_;
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

// TODO Is this safe?
int SpinDonor::max_quantum_number() const
{
  return static_cast<int>(electron_parameters_.get_quantum_number())
          + static_cast<int>(nuclear_parameters_.get_quantum_number());
}

CDouble SpinDonor::eigenvalue(const UInt level) const
{
  return static_cast<CDouble>(eigenvalue(energy_levels_[level-1]));
}

UInt SpinDonor::dimension() const
{
  return electron_parameters_.get_multiplicity()
         *nuclear_parameters_.get_multiplicity();
}

double SpinDonor::polarization(const UInt level) const
{
  return polarization(energy_levels_[level-1]);
}

UInt SpinDonor::orthogonal_level(const UInt level) const
{
  AdiabaticLabel adiabatic_label = energy_levels_[level-1];
  AdiabaticLabel orthogonal_adiabatic_label = orthogonal_level(adiabatic_label);
  return adiabatic_label_to_int_label(orthogonal_adiabatic_label);
}

} // namespace SpinDec

