// See SpinDonor.h for description.
// Seto Balian, Mar 12, 2014
// TODO double comparisons, make sure it's all safe ... test it.
// TODO Organise and clean up comments.

#include "SpinDec/SpinDonor.h"
#include "SpinDec/Errors.h"
#include <cmath>

namespace SpinDec
{

struct AdiabaticLabel // TODO Is this OK here?
{
  sign slot1;
  double slot2;
};

void SpinDonor::calc_energy_level_labels()
{  
  // In order of increasing energy, these are
  // |-,M-1> , |-,M-2> , ... , |-,-M>, |-,-M+1>, ... |+,+M>
  // where M = I + S

  double M = max_quantum_number();
  AdiabaticLabel label;
  
  // Fill |-,M-1> , |-,M-2> , ... , |-,-M>
  double m = M - 1.0;
  while (m >= -M) {
    label.slot1 = MINUS;
    label.slot2 = m;
    energy_level_labels_.push_back(label);
    m -= 1.0;
  }
  // Fill |-,-M+1>, ... |+,+M>
  m = -M+1.0;
  while (m <= M) {
    label.slot1 = PLUS;
    label.slot2 = m;
    m += 1.0;
    energy_level_labels_.push_back(label);
  }
  return;
}

void SpinDonor::build_graph()
{
  add_vertex(electron_);
  add_vertex(nucleus_);
  add_edge(0,1,hyperfine_.clone());
  return;
}

double SpinDonor::delta() const
{
  return
  - nucleus_.get_gyromagnetic_ratio() / electron_.get_gyromagnetic_ratio();
}

double SpinDonor::omega() const
{
  return electron_.get_gyromagnetic_ratio()*field_.get_magnitude();
}

double SpinDonor::scaled_omega() const
{
  return omega()/hyperfine_.get_strength();
}

double SpinDonor::D(const double quantum_number) const
{
  return quantum_number + scaled_omega()*(1.0 + delta());
}

double SpinDonor::O(const double quantum_number) const
{
  const double I = nucleus_.get_quantum_number();
  return std::sqrt( I*(I + 1.0) + 0.25 - std::pow(quantum_number,2) );
}

double SpinDonor::R(const double quantum_number) const
{
  return std::sqrt( std::pow(D(quantum_number),2) +
                    std::pow(O(quantum_number),2) );
}

// M rad s-1
double SpinDonor::eigenvalue(const AdiabaticLabel& label) const
{
  const double A = hyperfine_.get_strength();
  const double pm = sign_to_double(label.slot1);
  const double m = label.slot2;
  return (A/2.0)*(-0.5*(1.0 + 4.0*scaled_omega()*m*delta()) + pm*R(m));
}

unsigned int SpinDonor::adiabatic_label_to_int_label(
    const AdiabaticLabel& label) const
{
  
  const double pm = sign_to_double(label.slot1);
  const double m = label.slot2;
  unsigned int max_n = dimension();
  
  // energy_level_labels_ in increasing energy, so loop over these
  // and return loop variable when input label first matches
  // one in energy_level_labels_
  for (unsigned int i=0;i<max_n;i++) {
    if (( sign_to_double(energy_level_labels_[i].slot1) == pm) &&
        ( energy_level_labels_[i].slot2 == m)
       ) {
      return i;
    }
  }
  
  Errors::quit("Could not convert adiabatic label to integer label.");
  return 0;
  
}

AdiabaticLabel SpinDonor::orthogonal_label(AdiabaticLabel label) const
{
  
  // Deal with the case m = |M|
  if (label.slot2 == std::abs(max_quantum_number())) {
    return label;
  }
  
  // Switch slot1 PLUS <-> MINUS
  if (label.slot1 == PLUS) {
    label.slot2 = MINUS;
  } else {
      label.slot2 = PLUS;
  }
  return label;
  
}


double SpinDonor::cos_theta(const double quantum_number) const
{
  return D(quantum_number)/R(quantum_number);
}

double SpinDonor::sin_theta(const double quantum_number) const
{
  return O(quantum_number)/R(quantum_number);
}

double SpinDonor::a(const double quantum_number) const
{
  return (1.0/std::sqrt(2.0))*std::sqrt(1.0 + cos_theta(quantum_number));
}

double SpinDonor::b(const double quantum_number) const
{
  return (1.0/std::sqrt(2.0))*std::sqrt(1.0 - cos_theta(quantum_number));
}

double SpinDonor::polarization(const AdiabaticLabel& label) const
{
  return 0.5*sign_to_double(label.slot1)*
      std::pow(a(label.slot2),2.0) - std::pow(b(label.slot2),2.0);
}

SpinBasis SpinDonor::build_basis(const AdiabaticLabel& label) const
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
  const double pm = sign_to_double(label.slot1);
  const double m =  label.slot2;

  // Deal with the m = pm M cases
  if (std::abs(m) == max_quantum_number()) {
    basis_array = Eigen::ArrayXXd(1,2);
    if (m == -max_quantum_number()) {
      basis_array(0,0) = -0.5;
      basis_array(0,1) = -max_quantum_number()  + 0.5;
    } else {
        basis_array(0,0) = 0.5;
        basis_array(0,1) = max_quantum_number() - 0.5;
      }
  } else { // For all other cases (returning two basis states)
      basis_array = Eigen::ArrayXXd(2,2);
      if (pm == 1.0) {
        basis_array(0,0) = 0.5;
        basis_array(0,1) = m - 0.5;
        basis_array(1,0) = -0.5;
        basis_array(1,1) = m + 0.5;
      } else {
          basis_array(0,0) = -0.5;
          basis_array(0,1) = m + 0.5;
          basis_array(1,0) = 0.5;
          basis_array(1,1) = m - 0.5;
      }
    }
  return SpinBasis(basis_array);
}

SpinBasis SpinDonor::build_basis(const std::vector<AdiabaticLabel>& labels)
const
{

  // code avoids duplicate basis rows/entries
  
  // rows to build final basis array
  std::vector<Eigen::ArrayXd> rows;
    
  // loop over labels
  for (unsigned int i=0;i<labels.size();i++) {
    
    // get basis for level i
    Eigen::ArrayXXd single_level_basis =
        build_basis(labels[i]).get_basis_as_array();
    
    // loop over rows of basis for level i (this is either 1 or 2 rows)
    for (unsigned int j=0;j<single_level_basis.rows();j++) {
      
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
  for (unsigned int i=0;i<rows.size();i++) {
    num_rows += 1;
  }

  Eigen::ArrayXXd basis(num_rows,2);
  
  for (unsigned int i=0;i<rows.size();i++) {
    basis(i,0) = rows[i](0);
    basis(i,1) = rows[i](1);
  }
  
  return SpinBasis(basis);
  
}

SpinBasis SpinDonor::build_basis(const uivector& labels) const
{
  // convert vector of integer labels to adiabatic labels
  std::vector<AdiabaticLabel> adiabatic_labels;
  for (unsigned int i=0;i<labels.size();i++) {
    adiabatic_labels.push_back(energy_level_labels_[labels[i]]);
  }
  return build_basis(adiabatic_labels);
}


void SpinDonor::set_transition(const unsigned int upper_level,
                    const unsigned int lower_level)
{
  // check if levels valid
  
  if ( !(upper_level < dimension()) ) {
    Errors::quit("Upper donor level must be 0,1,...,dimension(donor).");
    return;
  }
  
  if ( !(lower_level < dimension()) ) {
    Errors::quit("Lower donor level must be 0,1,...,dimension(donor).");
    return;
  }
  
  if ( upper_level == lower_level ) {
    Errors::quit("Upper and lower donor levels must be different.");
    return;
  }
  
  if ( upper_level < lower_level ) {
    Errors::quit("Lower donor level must be smaller in value than upper.");
    return;
  }
  
  // all ok
  upper_level_ = upper_level;
  lower_level_ = lower_level;
  
  orthogonal_upper_level_ = orthogonal_label(upper_level);
  orthogonal_lower_level_ = orthogonal_label(lower_level);
  
  return;
  
}

SpinDonor::SpinDonor() : upper_level_(0),lower_level_(0),
    orthogonal_upper_level_(0),orthogonal_lower_level_(0)
{/**/}

SpinDonor::SpinDonor(const double field_strength,
    const double nucleus_quantum_number,
    const double electron_gyromagnetic_ratio,
    const double nucleus_gyromagnetic_ratio, const double hyperfine_strength,
    const unsigned int upper_level,
    const unsigned int lower_level)
: hyperfine_(Hyperfine(hyperfine_strength))
{
  field_ = UniformMagneticField(field_strength);
  electron_ = ElectronSpin(electron_gyromagnetic_ratio);
  nucleus_ = NuclearSpin(nucleus_quantum_number,nucleus_gyromagnetic_ratio);
  
  build_graph();
  calc_energy_level_labels();
  
  set_transition(upper_level,lower_level);
  
}

SpinDonor::SpinDonor(const double field_strength,
          const double nucleus_quantum_number,
          const double electron_gyromagnetic_ratio, // M rad s-1 T-1
          const double nucleus_gyromagnetic_ratio, // M rad s-1 T-1
          const double hyperfine_strength,        // M rad s-1
          const unsigned int upper_level,
          const unsigned int lower_level,
          const ThreeVector & electron_position, // Angstroms
          const ThreeVector & nucleus_position, // Angstroms
          const ComplexVector & electron_state,
          const ComplexVector & nucleus_state)
: hyperfine_(Hyperfine(hyperfine_strength))
{
  field_ = UniformMagneticField(field_strength);
  electron_ = ElectronSpin(electron_gyromagnetic_ratio,
      electron_position,electron_state);
  nucleus_ = NuclearSpin(nucleus_quantum_number,nucleus_gyromagnetic_ratio,
      nucleus_position,nucleus_state);
  
  build_graph();
  calc_energy_level_labels();
  
  set_transition(upper_level,lower_level);

}

const UniformMagneticField& SpinDonor::get_field() const
{
  return field_;
}

const ElectronSpin& SpinDonor::get_electron() const
{
  return electron_;
}

const NuclearSpin& SpinDonor::get_nucleus() const
{
  return nucleus_;
}

const Hyperfine& SpinDonor::get_hyperfine() const
{
  return hyperfine_;
}

double SpinDonor::max_quantum_number() const
{
  return electron_.get_quantum_number() + nucleus_.get_quantum_number();
}

cdouble SpinDonor::eigenvalue(const unsigned int level) const
{
  return static_cast<cdouble>(eigenvalue(energy_level_labels_[level]));
}

unsigned int SpinDonor::dimension() const
{
  return electron_.get_multiplicity()*nucleus_.get_multiplicity();
}

double SpinDonor::polarization(const unsigned int label) const
{
  return polarization(energy_level_labels_[label]);
}

SpinBasis SpinDonor::build_basis() const
{
  uivector labels;
  labels.push_back(upper_level_);
  labels.push_back(lower_level_);
  labels.push_back(orthogonal_upper_level_);
  labels.push_back(orthogonal_lower_level_);
  return build_basis(labels);
}

SpinBasis SpinDonor::build_complete_basis() const
{
  return SpinInteractionGraph::build_basis();
}

unsigned int SpinDonor::orthogonal_label(const unsigned int label) const
{
  AdiabaticLabel adiabatic_label = energy_level_labels_[label];
  AdiabaticLabel orthogonal_adiabatic_label = orthogonal_label(adiabatic_label);
  return adiabatic_label_to_int_label(orthogonal_adiabatic_label);
}


} // namespace SpinDec

