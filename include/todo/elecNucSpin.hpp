#ifndef ELECNUCSPIN_H
#define ELECNUCSPIN_H

// Electron coupled to a nucleus via the isotropic hyperfine interaction.
//
// Created  20/08/2012
// Modified 03/10/2012, 04/10/2012, 05/10/2012, 23/10/2012, 17/05/2013
// Seto Balian
// V1

// NOTE: Needs commenting and references

// NOTE: Eigenvector methods

#include "stdincludes.hpp"

#include "named.hpp"
#include "spin.hpp"
#include "spins.hpp"
#include "statevector.hpp"

using namespace std;
using namespace Eigen;

class elecNucSpin : public named
{

private:

  spins elec_nuc; // electron and nucleus (spin objects)
  double A;       // Hyperfine strength
  double B;       // Magnetic field

public:

  elecNucSpin();
  elecNucSpin(const string & name_in, spin elec_in, spin nuc_in, const double A_in, const double B_in);

  //////////////////////////////////////////////////////

  spins get_elec_nuc() const;
  spin get_elec() const;
  spin get_nuc() const;

  double get_A() const;
  double get_B() const;

  //////////////////////////////////////////////////////

  void set_elec_nuc(const spins & elec_nuc_in);
  void set_elec(const spin & elec_in);
  void set_nuc(const spin & nuc_in);
  void set_A(const double A_in);
  void set_B(const double B_in);

  //////////////////////////////////////////////////////

  double get_d() const;
  double get_omega() const;
  double get_scaled_omega() const;

  //////////////////////////////////////////////////////

  darray get_m() const;
  double pm_to_double(const char pm) const;
  double get_m_max() const;

  //////////////////////////////////////////////////////

  double get_D(const double m) const;
  double get_O(const double m) const;
  double get_R(const double m) const;

  //////////////////////////////////////////////////////

  double get_eigenvalue(const char pm,const double m) const;

  //////////////////////////////////////////////////////

  double get_cos_theta(const double m) const;
  double get_sin_theta(const double m) const;

  double get_a(const double m) const;
  double get_b(const double m) const;
  double get_polarization(const double m) const;

  //////////////////////////////////////////////////////

  MatrixXd get_high_field_basis(const char pm, const double m) const;
  MatrixXd get_high_field_basis(const char pm_1, const double m_1, const char pm_2, const double m_2) const;
//  MatrixXd get_high_field_basis(const char pm_1, const double m_1, const char pm_2, const double m_2, const bool Ising_only) const;
  MatrixXd get_high_field_basis(const int n_1, const int n_2) const;
//  MatrixXd get_high_field_basis(const int n_1, const int n_2, const bool Ising_only) const;

  //////////////////////////////////////////////////////

  pair<char,double> nLabel_to_adiabLabel(const int n) const;
  pair<char,double> nLabel_to_orthogonal_adiabLabel(const int n) const;
  int               adiabLabel_to_nLabel(const char pm, const double m) const;
  int               subspace_nLabel (const int n);
  ArrayXi           subspace_nLabels(const int n_1, const int n_2);
  ArrayXi           nLabels();
  int               subspace_dimension(const int n_1, const int n_2);
  int               dimension();

  //////////////////////////////////////////////////////
  double            effGyromagneticRatio(const int n_high, const int n_low) const;
  statevector       dominant_electron_state(const int n) const;

  //////////////////////////////////////////////////////
    
};

#endif // ELECNUCSPIN_H

