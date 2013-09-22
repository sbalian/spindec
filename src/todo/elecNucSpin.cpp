// Electron coupled to a nucleus via the isotropic hyperfine interaction.
//
// Created  20/08/2012
// Modified 03/10/2012, 04/10/2012, 05/10/2012, 10/10/2012, 23/10/2012
// Modified 11/12/2012 gamma_n -> - gamma_n
// Modified 26/02/2013, 17/05/2013
// Seto Balian
// V1

// NOTE: Needs commenting and references

// NOTE: m < m_max checks ...

// NOTE: GET THE SPIN UP AND DOWN CONSISTENT!

#include "stdincludes.hpp"

#include "elecNucSpin.hpp"

#include "named.hpp"
#include "spin.hpp"
#include "spins.hpp"
#include "statevector.hpp"

using namespace std;
using namespace Eigen;

elecNucSpin::elecNucSpin() : named("") {}

elecNucSpin::elecNucSpin(const string & name_in, spin elec_in, spin nuc_in, const double A_in, const double B_in) : named(name_in)
{
  elec_nuc.add(elec_in);
  elec_nuc.add(nuc_in);
  set_A(A_in);
  set_B(B_in);
}

//////////////////////////////////////////////////////

spins elecNucSpin::get_elec_nuc() const {
  return elec_nuc;
}

spin elecNucSpin::get_elec() const {
  return elec_nuc.get_spin_by_ID(0);
}

spin elecNucSpin::get_nuc() const {
  return elec_nuc.get_spin_by_ID(1);
}

double elecNucSpin::get_A() const {
  return A;
}

double elecNucSpin::get_B() const {
  return B;
}

//////////////////////////////////////////////////////

void elecNucSpin::set_elec_nuc(const spins & elec_nuc_in) {
  elec_nuc = elec_nuc_in;
  return;
}

void elecNucSpin::set_elec(const spin & elec_in) {
  elec_nuc.set_spin_by_ID(0, elec_in);
  return;
}

void elecNucSpin::set_nuc(const spin & nuc_in) {
  elec_nuc.set_spin_by_ID(1, nuc_in);
  return;
}

void elecNucSpin::set_A(const double A_in) {
  A = A_in;
  return;
}

void elecNucSpin::set_B(const double B_in) {
  B = B_in;
  return;
}

//////////////////////////////////////////////////////

double elecNucSpin::get_d() const {
  return -get_nuc().get_gyromagneticRatio() / get_elec().get_gyromagneticRatio();
}

double elecNucSpin::get_omega() const {
  return get_elec().get_gyromagneticRatio()*B;
}

double elecNucSpin::get_scaled_omega() const {
  return get_omega()/A;
}

//////////////////////////////////////////////////////

darray elecNucSpin::get_m() const {
  darray m_values;
  double m_max = get_m_max();
  double m     = - m_max;
  while (m<=m_max) {
    m_values.push_back ( m );
    m = m + 1.0;
  }
  return m_values;
}

double elecNucSpin::pm_to_double(const char pm) const {

  int p_or_m = 0;
  if (pm == '+') {p_or_m = 1;}
  if (pm == '-') {p_or_m = 2;}

  switch(p_or_m)
  {
    case 1:
      return  1.0;
    case 2:
      return -1.0;
    default:
      cout << error_by_name() << "char pm must be '+' or '-'. Quitting ..." << endl;
      exit(1);
      return 0.0;
  }

}

double elecNucSpin::get_m_max() const {
  return get_elec().get_spinQN_as_double() + get_nuc().get_spinQN_as_double();
}

//////////////////////////////////////////////////////

double elecNucSpin::get_D(const double m) const {
  return m + get_scaled_omega()*(1.0 + get_d());
}

double elecNucSpin::get_O(const double m) const {
  double I = get_nuc().get_spinQN_as_double();
  return sqrt( I*(I + 1.0) + 0.25 - m*m );
}

double elecNucSpin::get_R(const double m) const {
  return sqrt ( pow(get_D(m),2.0) + pow(get_O(m),2.0) );
}

//////////////////////////////////////////////////////

double elecNucSpin::get_eigenvalue(const char pm, const double m) const {
  return (get_A()/2.0)*(-0.5*(1.0 + 4.0*get_scaled_omega()*m*get_d()) + pm_to_double(pm)*get_R(m) ); 
}

//////////////////////////////////////////////////////

double elecNucSpin::get_cos_theta(const double m) const {
  return get_D(m)/get_R(m);
}

double elecNucSpin::get_sin_theta(const double m) const {
  return get_O(m)/get_R(m);
}

double elecNucSpin::get_a(const double m) const {
  return (1.0/sqrt(2.0))*sqrt(1.0 + get_cos_theta(m));
}

double elecNucSpin::get_b(const double m) const {
  return (1.0/sqrt(2.0))*sqrt(1.0 - get_cos_theta(m));
}

double elecNucSpin::get_polarization(const double m) const {
  return pow(get_a(m),2.0) - pow(get_b(m),2.0);
}

//////////////////////////////////////////////////////

MatrixXd elecNucSpin::get_high_field_basis(const char pm, const double m) const {

  MatrixXd out;
  if (abs(m) == get_m_max()) { // NOTE: m is a double, will it always be exactly 5.0 for example?
    out = MatrixXd(1,2);
    if (m == -get_m_max()) {
      out(0,0) = -0.5;
      out(0,1) = -get_m_max() + 0.5;
    } else {
        out(0,0) = 0.5;
        out(0,1) = get_m_max() - 0.5;
      }
    return out;
  } else {
      out = MatrixXd(2,2);
      out(0,0) = 0.5;
      out(0,1) = m - 0.5;
      out(1,0) = -0.5;
      out(1,1) = m + 0.5;
      return out;
    }

}

//MatrixXd elecNucSpin::get_high_field_basis(const char pm, const double m) const {

//  MatrixXd out;
//  if (abs(m) == get_m_max()) { // NOTE: m is a double, will it always be exactly 5.0 for example?
//    out = MatrixXd(2,2);
//    if (m == -get_m_max()) {
//      out(0,0) = -0.5;
//      out(0,1) = -get_m_max() + 0.5;
//      out(1,0) = 0.5;
//      out(1,1) = -get_m_max() + 0.5;
//    } else {
//        out(0,0) = 0.5;
//        out(0,1) = get_m_max() - 0.5;
//        out(1,0) = -0.5;
//        out(1,1) = get_m_max() - 0.5;
//      }
//    return out;
//  } else {
//      out = MatrixXd(4,2);
//      out(0,0) = 0.5;
//      out(0,1) = m - 0.5;
//      out(1,0) = -0.5;
//      out(1,1) = m + 0.5;
//      out(2,0) = -0.5;
//      out(2,1) = m - 0.5;
//      out(3,0) = 0.5;
//      out(3,1) = m + 0.5;
//      return out;
//    }

//}

//MatrixXd elecNucSpin::get_high_field_basis(const char pm_1, const double m_1, const char pm_2, const double m_2, const bool Ising_only) const {
MatrixXd elecNucSpin::get_high_field_basis(const char pm_1, const double m_1, const char pm_2, const double m_2) const {

  MatrixXd temp_out;

  MatrixXd basis_1 = get_high_field_basis(pm_1, m_1);
  MatrixXd basis_2 = get_high_field_basis(pm_2, m_2);

  MatrixXd basis_3;
  MatrixXd basis_4;

  if ( abs(m_1) != get_m_max() ) {
    if (pm_to_double(pm_1) == 1.0) {
      basis_3 = get_high_field_basis('-', m_1);
    } else {
        basis_3 = get_high_field_basis('+', m_1);
      } 
  } else {
      basis_3 = basis_1;
    }

  if ( abs(m_2) != get_m_max() ) {
    if (pm_to_double(pm_2) == 1.0) {
      basis_4 = get_high_field_basis('-', m_2);
    } else {
        basis_4 = get_high_field_basis('+', m_2);
      } 
  } else {
      basis_4 = basis_2;
    }

  temp_out = MatrixXd( basis_1.rows() + basis_2.rows() + basis_3.rows() + basis_4.rows() , 2);

  int i, j;
  j = 0;
  for (i=0;i<basis_1.rows();i++) {
    temp_out.row(j) = basis_1.row(i);
    j = j + 1;
  }
  for (i=0;i<basis_2.rows();i++) {
    temp_out.row(j) = basis_2.row(i);
    j = j + 1;
  }
  for (i=0;i<basis_3.rows();i++) {
    temp_out.row(j) = basis_3.row(i);
    j = j + 1;
  }
  for (i=0;i<basis_4.rows();i++) {
    temp_out.row(j) = basis_4.row(i);
    j = j + 1;
  }

  MatrixXd temp_out_1(temp_out.rows(),3);
  for (i=0;i<temp_out_1.rows();i++) {
    temp_out_1(i,0) = temp_out(i,0);
    temp_out_1(i,1) = temp_out(i,1);
    temp_out_1(i,2) = 1.0;
  }

  vector<RowVectorXd> rows_to_keep;

  for (i=0;i<temp_out_1.rows();i++) {
    if (temp_out_1(i,2) == 0.0) {continue;}
    j = 0;
    while ( j < i ) {
      if  ( ( temp_out_1(j,0) == temp_out_1(i,0) ) && ( temp_out_1(j,1) == temp_out_1(i,1) ) ) {
        temp_out_1(j,2) = 0.0;
      }
      j = j + 1;
    }
  }


  RowVectorXd temp_row(2);
  for (i=0;i<temp_out_1.rows();i++) {
    if (temp_out_1(i,2) == 1.0) {
      temp_row(0) = temp_out_1(i,0);
      temp_row(1) = temp_out_1(i,1);
      rows_to_keep.push_back ( temp_row );
    }
  }

  MatrixXd out(int(rows_to_keep.size()), 2);
  for (i=0;i<int(rows_to_keep.size());i++) {
    out.row(i) = rows_to_keep[i];
  }

//  if (Ising_only == 1) {
    return out;
//  }

//  // identity unique mI
//  vector<double> unique_mI;
//  for (i=0;i<out.rows();i++) {
//    unique_mI.push_back( out(i,1) );
//  }

//  vector<double>::iterator it;
//  it = unique (unique_mI.begin(), unique_mI.end());
//  unique_mI.resize( std::distance(unique_mI.begin(),it) );

//  int unique_mI_count = static_cast<int>(unique_mI.size());

//  MatrixXd fullHFout(unique_mI_count*2,2);

//  
//  int k = -1;
//  for (i=0;i<unique_mI_count*2;i++) {

//    if((i%2) == 0) {
//      fullHFout(i,1)  = unique_mI[k];
//      k+=1;
//      fullHFout(i,0)  = 0.5;
//    } else {
//        fullHFout(i,0)  = -0.5;
//      }
//    fullHFout(i,1)  = unique_mI[k];
//  }

//  return fullHFout;

}

//MatrixXd elecNucSpin::get_high_field_basis(const int n_1, const int n_2, const bool Ising_only) const {
//  return get_high_field_basis(nLabel_to_adiabLabel(n_1).first,
//                            nLabel_to_adiabLabel(n_1).second,
//                            nLabel_to_adiabLabel(n_2).first,
//                            nLabel_to_adiabLabel(n_2).second, Ising_only); 
//}

MatrixXd elecNucSpin::get_high_field_basis(const int n_1, const int n_2) const {
  return get_high_field_basis(nLabel_to_adiabLabel(n_1).first,
                            nLabel_to_adiabLabel(n_1).second,
                            nLabel_to_adiabLabel(n_2).first,
                            nLabel_to_adiabLabel(n_2).second); 
}

//////////////////////////////////////////////////////

pair<char,double> elecNucSpin::nLabel_to_adiabLabel(const int n) const {

  pair<char,double> out;

  int n_max = elec_nuc.get_multiplicity();

  if ((n > n_max) || (n < 1)) {
    cout << error_by_name() << "n must be an integer in the range 1 <= n <= " << n_max << ". Quitting ..." << endl; 
    exit(1);
    return out;
  }

  double m_max = get_m_max();

  int i;
  double m = m_max;
  char pm = '-';

  for (i=1;i<=n;i++) {

    if ((m >= - m_max) && (pm == '-')) {
      m = m - 1.0;
    }
    
    if (m == - m_max - 1.0) {
      pm = '+';
      m = m + 1.0;
    }

    if (pm == '+') {
      m = m + 1.0;
    }

  }

  out.first = pm;
  out.second = m;

  return out;

}

pair<char,double> elecNucSpin::nLabel_to_orthogonal_adiabLabel(const int n) const {

  pair<char,double> out = nLabel_to_adiabLabel(n);

  if ( abs(out.second) == get_m_max() ) {
    return out;
  } else {
      if (out.first == '+') {
        out.first = '-';
        return out;
      } else {
          out.first = '+';
          return out;
        }
    }

}

int elecNucSpin::adiabLabel_to_nLabel(const char pm, const double m) const {

  int i;
  int n_max = elec_nuc.get_multiplicity();

  vector<int>     n_vec;
  vector< pair<char,double> > adiab_vec;

  for (i=1;i<=n_max;i++) {
    n_vec.push_back(i);
    adiab_vec.push_back ( nLabel_to_adiabLabel(i) );
  }

  for (i=0;i<n_max;i++) {
    if ((pm == adiab_vec[i].first) && (m == adiab_vec[i].second)) {
      return n_vec[i];
    }
  }

  return 0;

}

int elecNucSpin::subspace_nLabel(const int n) {
  return adiabLabel_to_nLabel ( nLabel_to_orthogonal_adiabLabel(n).first, nLabel_to_orthogonal_adiabLabel(n).second );
}

ArrayXi elecNucSpin::subspace_nLabels(const int n_1, const int n_2) {

  int n_3, n_4;

  n_3 = subspace_nLabel(n_1);
  n_4 = subspace_nLabel(n_2);

  MatrixXi out_temp(4,2);
  out_temp << n_1, 1,
              n_2, 1,
              n_3, 1,
              n_4, 1;

  vector<double> to_keep;

  int i,j;
  for (i=0;i<out_temp.rows();i++) {
    if (out_temp(i,1) == 0) {continue;}
    j = 0;
    while ( j < i ) {
      if  (  out_temp(j,0) == out_temp(i,0) )  {
        out_temp(j,1) = 0;
      }
      j = j + 1;
    }
  }

  for (i=0;i<out_temp.rows();i++) {
    if (out_temp(i,1) == 1) {
      to_keep.push_back ( out_temp(i,0) );
    }
  }

  ArrayXi out(int(to_keep.size()));
  for (i=0;i<out.rows();i++) {
    out(i) = to_keep[i];
  }

  return out;

}

ArrayXi   elecNucSpin::nLabels() {
  ArrayXi out( dimension() );
  int i;
  for (i=1;i<=dimension();i++) {
    out(i - 1) = i;
  }
  return out;
}

int     elecNucSpin::subspace_dimension(const int n_1, const int n_2) {
  return subspace_nLabels(n_1,n_2).rows();
}

int   elecNucSpin::dimension() {
  return elec_nuc.get_multiplicity();
}

//////////////////////////////////////////////////////
double     elecNucSpin::effGyromagneticRatio(const int n_high, const int n_low) const {
  
  double pmH = pm_to_double( nLabel_to_adiabLabel ( n_high ).first );
  double pmL = pm_to_double( nLabel_to_adiabLabel ( n_low ).first );
  double mH  = nLabel_to_adiabLabel ( n_high ).second;
  double mL  = nLabel_to_adiabLabel ( n_low ).second;

  double II = get_nuc().get_spinQN_as_double();

  double AA = get_A();
  double BB = get_B();
  double gammaE = get_elec().get_gyromagneticRatio();
  double gammaN = -get_nuc().get_gyromagneticRatio();

  // From Mathematica
  double dfdB = 0.5*AA*(-((2.0*gammaN*mH)/AA) + (
    gammaE*(1.0 + gammaN/gammaE)*((BB*gammaE*(1.0 + gammaN/gammaE))/AA + 
       mH)*pmH)/(
    AA*sqrt(0.25 + II*(1.0 + II) - 
      pow(mH,2.0) + pow((BB*gammaE*(1.0 + gammaN/gammaE))/AA + mH,2.0)))) - 
0.5*AA*(-((2.0*gammaN*mL)/AA) + (
    gammaE*(1.0 + gammaN/gammaE)*((BB*gammaE*(1.0 + gammaN/gammaE))/AA + 
       mL)*pmL)/(
    AA*sqrt(0.25 + II*(1.0 + II) - 
      pow(mL,2.0) + pow((BB*gammaE*(1.0 + gammaN/gammaE))/AA + mL,2.0))));
  
  return dfdB;

}

statevector   elecNucSpin::dominant_electron_state(const int n) const {

  VectorXcd out(2);

  double pm = pm_to_double ( nLabel_to_adiabLabel(n).first );
  double m  = nLabel_to_adiabLabel(n).second;

  if (pm == 1.0) {
    if (get_a(m) >= get_b(m)) {
      out(0) = cmplxd(0.0,0.0);
      out(1) = cmplxd(1.0,0.0);
    } else {
        out(0) = cmplxd(1.0,0.0);
        out(1) = cmplxd(0.0,0.0);
      }
    
  } else {
      if (get_a(m) >= get_b(m)) {
        out(0) = cmplxd(1.0,0.0);
        out(1) = cmplxd(0.0,0.0);
      } else {
          out(0) = cmplxd(0.0,0.0);
          out(1) = cmplxd(1.0,0.0);
        }

  }

  return statevector(out);
  
}

//////////////////////////////////////////////////////

////////////////////////////////////////////////////////
//// TEST //
//// g++ -I/home/sbalian/eigen/ -I/home/sbalian/phys/cce/V1/include/ ./elecNucSpin.cpp ./named.cpp ./spin.cpp ./spins.cpp ./statevector.cpp -o ZZZ
////////////////////////////////////////////////////////

//int main () {

//  double B = 0.480;
////  double B = 0.18821;

//  frac spinQN;
//  spinQN.num = 1;
//  spinQN.den = 2;

//  spin electron("Electron", 0, spinQN , 1.7591e05);

//  spinQN.num = 9;
//  spinQN.den = 2;

//  spin bismuth("Bismuth", 0, spinQN , -43.744);

//  double A = 9.2702e3;

//  elecNucSpin donor("e-Bi",electron,bismuth,A,B);

////  cout << donor.get_high_field_basis(9,12) << endl;

////  cout << endl;

////  cout << donor.get_high_field_basis(10,11) << endl;

////  cout << endl;

////  cout << donor.get_high_field_basis(20,1) << endl;

////  cout << endl;

////  cout << "20" << endl;
////  cout << donor.nLabel_to_adiabLabel(20).first << " " << donor.nLabel_to_adiabLabel(20).second << endl;
////  cout << "1" << endl;
////  cout << donor.nLabel_to_adiabLabel(1).first  << " " << donor.nLabel_to_adiabLabel(1).second << endl;
////  cout << "20'" << endl;
////  cout << donor.nLabel_to_orthogonal_adiabLabel(20).first << " " << donor.nLabel_to_orthogonal_adiabLabel(20).second << endl;
////  cout << "1'" << endl;
////  cout << donor.nLabel_to_orthogonal_adiabLabel(1).first << " " << donor.nLabel_to_orthogonal_adiabLabel(1).second << endl;

////  cout << "12" << endl;
////  cout << donor.nLabel_to_adiabLabel(12).first << " " << donor.nLabel_to_adiabLabel(12).second << endl;
////  cout << "9" << endl;
////  cout << donor.nLabel_to_adiabLabel(9).first  << " " << donor.nLabel_to_adiabLabel(9).second << endl;
////  cout << "12'" << endl;
////  cout << donor.nLabel_to_orthogonal_adiabLabel(12).first << " " << donor.nLabel_to_orthogonal_adiabLabel(12).second << endl;
////  cout << "9'" << endl;
////  cout << donor.nLabel_to_orthogonal_adiabLabel(9).first << " " << donor.nLabel_to_orthogonal_adiabLabel(9).second << endl;


////  cout << "10" << endl;
////  cout << donor.nLabel_to_adiabLabel(10).first << " " << donor.nLabel_to_adiabLabel(10).second << endl;
////  cout << "10'" << endl;
////  cout << donor.nLabel_to_orthogonal_adiabLabel(10).first  << " " << donor.nLabel_to_orthogonal_adiabLabel(10).second << endl;

////  cout << "20" << endl;
////  cout << donor.nLabel_to_adiabLabel(20).first << " " << donor.nLabel_to_adiabLabel(20).second << endl;
////  cout << "20'" << endl;
////  cout << donor.nLabel_to_orthogonal_adiabLabel(20).first  << " " << donor.nLabel_to_orthogonal_adiabLabel(20).second << endl;

////  cout << endl;
////  cout << "12 -> 9" << endl;
////  cout << donor.subspace_nLabels(12,9) << endl;
////  cout << "11 -> 10" << endl;
////  cout << donor.subspace_nLabels(11,10) << endl;
////  cout << "11 -> 10 dim = " << donor.subspace_dimension(11,10) << endl;
////  cout << "12 -> 9 dim = " <<  donor.subspace_dimension(12,9) << endl;

////  cout << endl;
////  cout << "20 -> 1" << endl;
////  cout << donor.subspace_nLabels(20,1) << endl;
////  cout << "20 -> 1 dim = " << donor.subspace_dimension(20,1) << endl;


////  cout << donor.nLabel_to_orthogonal_adiabLabel(10).first << " " << donor.nLabel_to_orthogonal_adiabLabel(10).second << endl;

////  cout << donor.effGyromagneticRatio(12,9) << endl;

//donor.dominant_electron_state(10).print();

//  return 0;

//}






