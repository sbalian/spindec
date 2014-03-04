// See SpinDonor.h for description.
// Seto Balian, Mar 4, 2014
// TODO double comparisons, make sure it's all safe ...
// TODO needs commenting
// TODO Can be improved a lot

#include "SpinDonor.h"
#include "Errors.h"
#include <cmath>

namespace SpinDecoherence
{

struct AdiabaticLabel // TODO Is this OK here?
{
  sign slot1;
  double slot2;
};

void SpinDonor::calc_energy_level_labels()
{
  // TODO is this method safe with doubles?
  
  // In order of increasing energy, these are
  // |-,M-1> , |-,M-2> , ... , |-,-M>, |-,-M+1>, ... |+,+M>
  // where M = I + S

  double M = max_quantum_number();
  double m = M - 1.0;
  AdiabaticLabel label;
  
  while (m >= -M) {
    label.slot1 = MINUS;
    label.slot2 = m;
    energy_level_labels_.push_back(label);
    m -= 1.0;
  }
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
  add_edge(0,1,&hyperfine_);
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
  return sign_to_double(label.slot1)*
      std::pow(a(label.slot2),2.0) - std::pow(b(label.slot2),2.0);
}

SpinBasis SpinDonor::build_basis(const AdiabaticLabel& label) const
{
  Eigen::ArrayXXd basis_array;
  const double pm = sign_to_double(label.slot1);
  const double m =  label.slot2;

  if (std::abs(m) == max_quantum_number()) {
    basis_array = Eigen::ArrayXXd(1,2);
    if (m == -max_quantum_number()) {
      basis_array(0,0) = -0.5;
      basis_array(0,1) = -max_quantum_number()  + 0.5;
    } else {
        basis_array(0,0) = 0.5;
        basis_array(0,1) = max_quantum_number() - 0.5;
      }
  } else {
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

// TODO This methods desperately needs commenting ...
SpinBasis SpinDonor::build_basis(const AdiabaticLabel& label1,
                                 const AdiabaticLabel& label2) const
{
  Eigen::ArrayXXd temp_basis;

  Eigen::ArrayXXd basis1 = build_basis(label1).get_basis_as_array();
  Eigen::ArrayXXd basis2 = build_basis(label2).get_basis_as_array();

  Eigen::ArrayXXd basis3;
  Eigen::ArrayXXd basis4;
  
  const double pm1 = sign_to_double(label1.slot1);
  const double pm2 = sign_to_double(label2.slot1);
  
  const double m1 = label1.slot2;
  const double m2 = label2.slot2;
  
  AdiabaticLabel temp_label;
  
  if ( std::abs(m1) != max_quantum_number() ) {
    if (pm1 == 1.0) {
      temp_label.slot1 = MINUS;
      temp_label.slot2 = m1;
      basis3 = build_basis(temp_label).get_basis_as_array();
    } else {
        temp_label.slot1 = PLUS;
        temp_label.slot2 = m1;
        basis3 = build_basis(temp_label).get_basis_as_array();
      }
  } else {
      basis3 = basis1;
    }

  if ( std::abs(m2) != max_quantum_number() ) {
    if (pm2 == 1.0) {
      temp_label.slot1 = MINUS;
      temp_label.slot2 = m2;
      basis4 = build_basis(temp_label).get_basis_as_array();
    } else {
        temp_label.slot1 = PLUS;
        temp_label.slot2 = m2;
        basis4 = build_basis(temp_label).get_basis_as_array();
      } 
  } else {
      basis4 = basis2;
    }

  temp_basis = Eigen::ArrayXXd(basis1.rows() +
                               basis2.rows() +
                               basis3.rows() +
                               basis4.rows() , 2);

  int i = 0;
  int j = 0;
  
  j = 0;
  for (i=0;i<basis1.rows();i++) {
    temp_basis.row(j) = basis1.row(i);
    j = j + 1;
  }
  for (i=0;i<basis2.rows();i++) {
    temp_basis.row(j) = basis2.row(i);
    j = j + 1;
  }
  for (i=0;i<basis3.rows();i++) {
    temp_basis.row(j) = basis3.row(i);
    j = j + 1;
  }
  for (i=0;i<basis4.rows();i++) {
    temp_basis.row(j) = basis4.row(i);
    j = j + 1;
  }

  Eigen::ArrayXXd temp_basis1(temp_basis.rows(),3);
  for (i=0;i<temp_basis1.rows();i++) {
    temp_basis1(i,0) = temp_basis(i,0);
    temp_basis1(i,1) = temp_basis(i,1);
    temp_basis1(i,2) = 1.0;
  }

  std::vector<Eigen::ArrayXd> rows_to_keep;

  for (i=0;i<temp_basis1.rows();i++) {
    if (temp_basis1(i,2) == 0.0) {continue;}
    j = 0;
    while ( j < i ) {
      if  ( ( temp_basis1(j,0) == temp_basis1(i,0) ) &&
          ( temp_basis1(j,1) == temp_basis1(i,1) ) ) {
        temp_basis1(j,2) = 0.0;
      }
      j = j + 1;
    }
  }

  Eigen::ArrayXd temp_row(2);
  for (i=0;i<temp_basis1.rows();i++) {
    if (temp_basis1(i,2) == 1.0) {
      temp_row(0) = temp_basis1(i,0);
      temp_row(1) = temp_basis1(i,1);
      rows_to_keep.push_back ( temp_row );
    }
  }

  Eigen::ArrayXXd basis(int(rows_to_keep.size()), 2);
  for (i=0;i<int(rows_to_keep.size());i++) {
    basis.row(i) = rows_to_keep[i];
  }

    return SpinBasis(basis);
}

SpinBasis SpinDonor::build_basis(const unsigned int label1,
                      const unsigned int label2) const
{
  return build_basis(energy_level_labels_[label1],energy_level_labels_[label2]);
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
  
}

SpinDonor::SpinDonor() : upper_level_(0),lower_level_(0)
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
          const d3vector & electron_position, // Angstroms
          const d3vector & nucleus_position, // Angstroms
          const cdvector & electron_state,
          const cdvector & nucleus_state)
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
  return build_basis(upper_level_,lower_level_);
}

SpinBasis SpinDonor::build_complete_basis() const
{
  return SpinInteractionGraph::build_basis();
}

} // namespace SpinDecoherence

