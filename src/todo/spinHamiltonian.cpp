// Static methods to fill a spin Hamiltonian
//
// Created  04/09/2012
// Modified 19/09/2012, 20/09/2012, 22/09/2012, 26/09/2012, 27/09/2012, 28/09/2012, 02/10/2012, 19/11/2012, 24/11/2012
// Modified 11/12/2012 - fixed symptomless bug from continue vs break mistake
// Modified 18/03/2013, 16/05/2013, 17/05/2013
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "qoperator.hpp"
#include "spinHamiltonian.hpp"
#include "spins.hpp"

// NOTE: Comments may need updating
// NOTE: Checks? e.g. basis built?

using namespace Eigen;

void spinHamiltonian::Dipolar(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
                               const int spin_ID_1, const int spin_ID_2, const double strength)
{

  //char switch_or_no = 'y';

  // Get spin quantum numbers
  double S1 = spins_in.get_spin_by_ID(spin_ID_1).get_spinQN_as_double();
  double S2 = spins_in.get_spin_by_ID(spin_ID_2).get_spinQN_as_double();

  // Dimension Hilbert space
  int dim = hamiltonian.dimension();

  // Number of spins
  int nspins = spins_in.size();

  // Loop variables
  int i,j,p;

  // Magnetic quantum numbers (labeled)
  double m1_i, m1_j; 
  double m2_i, m2_j;
  double m_other_i, m_other_j;

  // Coefficients from spin raising and lowering operators
  double coeff_1, coeff_2;
  
  // Test variables  
  int valid, reject;                              
  double delta_m1, delta_m2;
  
      
  // Fill matrix elements, sieving out zeros. Calculate:
  // D S_1^z S_2^z - (D / 4) (S_1^+ S_2^- + S_1^- S_2^+)
  // D: dipolar coupling strength
  // S_1,S_2: (vector) spin operators
  // S_1^z,S_2^z: z-component of the spin operators (magnetic field along z)
  // S_1^+,S_1^-,S_2^+,S_2^-: spin raising and lowering operators

  for (i=0; i<dim; i++) {
  
    // Calculate Ising part: D S_1^z S_2^z
    // Matrix elements <i| H_dipolar |j> (i == j)
    m1_i = high_field_basis(i,spin_ID_1);
    m2_i = high_field_basis(i,spin_ID_2);

    hamiltonian.set_element( i, i, hamiltonian.get_element(i,i)
      +  cmplxd(strength*m1_i*m2_i,0.0) );
    
    // Calculate flip-flop part: - (D / 4) (S_1^+ S_2^- + S_1^- S_2^+)
    // sieving out zeros
    // Matrix elements <i| H_dipolar |j> (i != j)
    for (j=0; j<dim; j++) {
    
      // Initialise test variables
      reject     = 0;
      valid      = 0;

      // Off-diagonals only
      if (i==j) {
        continue;
      }

      // If the ith and jth magnetic quantum numbers differ for any of the other spins,
      // matrix element is zero
      for (p=0;p<nspins;p++) {
        if ((p != spin_ID_1) && (p != spin_ID_2)) {
          m_other_i = high_field_basis(i,p);
          m_other_j = high_field_basis(j,p);
          if (m_other_i != m_other_j) {
            reject = 1;
            break;
          }
        }
      }
      if (reject == 1) {continue;}

      // Calculate m1_j, m2_j, delta_m1, delta_m2
      m1_j = high_field_basis(j,spin_ID_1);
      m2_j = high_field_basis(j,spin_ID_2);
      delta_m1 = m1_i - m1_j;
      delta_m2 = m2_i - m2_j;
      
    
      // if |delta_m1| or |delta_m2| are more than 1, reject the matrix element
      if ( (abs(delta_m1) > 1.0) || (abs(delta_m2) > 1.0) ) {
        continue;
      }
      
      // now test
      // 1) delta_m = +\- 1
      // 2) delta_m1 = - delta_m2
      if(delta_m1*delta_m2 == -1.0) {
        valid = 1;
      }

      if(valid == 0) {continue;}

      // END OF SIEVE
      // If valid = 1 work out matrix element

//      cout << "Change?" <<  endl;
//      cin >> switch_or_no;
//      if (switch_or_no == 'y') {
//        delta_m1 = -1.0;
//        cout << "changed" << endl;
//      } else {
//          cout << "not changed" << endl;
//        }

      // Off diagonal term : - <i |D *(1/4) [ S2+S1- + S2-S1+ ] | j>
      if( delta_m1 == -1.0) {
        // work out - < m1 -1  m2 +1 | D*(1/4)[S2+S1-]| m1 m2..>
        coeff_1 = S1*(S1+1.0) - m1_j*(m1_j-1.0);
        coeff_2 = S2*(S2+1.0) - m2_j*(m2_j+1.0);
        hamiltonian.set_element(i,j, hamiltonian.get_element(i,j) - cmplxd(strength*0.25*sqrt(coeff_1*coeff_2),0.0 ) );
      
      } else {
          
          // work out < m1 +1  m2 -1 | A*(1/2)[S2-S1+]|   m1 m2..>
          coeff_1 = S1*(S1+1.0) - m1_j*(m1_j+1.0);
          coeff_2 = S2*(S2+1.0) - m2_j*(m2_j-1.0);
          hamiltonian.set_element( i,j,hamiltonian.get_element(i,j) - cmplxd(strength*0.25*sqrt(coeff_1*coeff_2),0.0 ) );
        
        }
        
    }
    

  }


  return;

}


void spinHamiltonian::Dipolar(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
                                            const int spin_ID_1, const int spin_ID_2, const double strength, const bool Ising_only)
                                                                                          // dipolar
{
  if (Ising_only == 1) {
    Ising(hamiltonian, spins_in, high_field_basis, spin_ID_1, spin_ID_2, strength);
  } else {
      Dipolar(hamiltonian, spins_in, high_field_basis, spin_ID_1, spin_ID_2, strength);
    }
  return;
}



void spinHamiltonian::Ising(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
                                     const int spin_ID_1, const int spin_ID_2, const double strength)
                                                                                        // hyperfine
{
  // Dimension Hilbert space
  int dim   = hamiltonian.dimension();

  // Loop variables
  int i;

  // Magnetic quantum numbers (labeled)
  double m1_i; 
  double m2_i;
      
  // Fill matrix elements. Calculate:
  // A S_1^z S_2^z
  // A: coupling strength
  // S_1^z,S_2^z: z-component of the spin operators (magnetic field along z)

  for (i=0; i<dim; i++) {
    // Calculate Ising part: A S_1^z S_2^z
    // Matrix elements <i| H_isohyperfine |j> (i == j)
    m1_i = high_field_basis(i,spin_ID_1);
    m2_i = high_field_basis(i,spin_ID_2);
    hamiltonian.set_element( i,i, hamiltonian.get_element(i,i)
      +  cmplxd(strength*m1_i*m2_i,0.0) );
  }
  return;
}


void spinHamiltonian::IsoHyperfine(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
                                            const int spin_ID_1, const int spin_ID_2, const double strength)
                                                                                          // hyperfine
{

  // Get spin quantum numbers
  double S1 = spins_in.get_spin_by_ID(spin_ID_1).get_spinQN_as_double();
  double S2 = spins_in.get_spin_by_ID(spin_ID_2).get_spinQN_as_double();

  // Dimension Hilbert space
  int dim   = hamiltonian.dimension();

  // Number of spins
  int nspins = spins_in.size();

  // Loop variables
  int i,j,p;

  // Magnetic quantum numbers (labeled)
  double m1_i, m1_j; 
  double m2_i, m2_j;
  double m_other_i, m_other_j;

  // Coefficients from spin raising and lowering operators
  double coeff_1, coeff_2;
  
  // Test variables  
  int valid, reject;                              
  double delta_m1, delta_m2;
      
  // Fill matrix elements, sieving out zeros. Calculate:
  // A S_1.S_2 = A S_1^z S_2^z + (A / 2) (S_1^+ S_2^- + S_1^- S_2^+)
  // A: coupling strength
  // S_1,S_2: (vector) spin operators
  // S_1^z,S_2^z: z-component of the spin operators (magnetic field along z)
  // S_1^+,S_1^-,S_2^+,S_2^-: spin raising and lowering operators

  for (i=0; i<dim; i++) {
  
    // Calculate Ising part: A S_1^z S_2^z
    // Matrix elements <i| H_isohyperfine |j> (i == j)
    m1_i = high_field_basis(i,spin_ID_1);
    m2_i = high_field_basis(i,spin_ID_2);

    hamiltonian.set_element(i,i, hamiltonian.get_element(i,i)
      +  cmplxd(strength*m1_i*m2_i,0.0));
    
    // Calculate flip-flop part: (A / 2) (S_1^+ S_2^- + S_1^- S_2^+)
    // sieving out zeros
    // Matrix elements <i| H_isohyperfine |j> (i != j)
    for (j=0; j<dim; j++) {
    
      // Initialise test variables
      reject     = 0;
      valid      = 0;

      // Off-diagonals only
      if (i==j) {
        continue;
      }

      // If the ith and jth magnetic quantum numbers differ for any of the other spins,
      // matrix element is zero
      for (p=0;p<nspins;p++) {
        if ((p != spin_ID_1) && (p != spin_ID_2)) {
          m_other_i = high_field_basis(i,p);
          m_other_j = high_field_basis(j,p);
          if (m_other_i != m_other_j) {
            reject = 1;
            break;
          }
        }
      }
      if (reject == 1) {continue;}

      // Calculate m1_j, m2_j, delta_m1, delta_m2
      m1_j = high_field_basis(j,spin_ID_1);
      m2_j = high_field_basis(j,spin_ID_2);
      delta_m1 = m1_i - m1_j;
      delta_m2 = m2_i - m2_j;
      
    
      // if |delta_m1| or |delta_m2| are more than 1, reject the matrix element
      if ( (abs(delta_m1) > 1.0) || (abs(delta_m2) > 1.0) ) {
        continue;
      }
      
      // now test
      // 1) delta_m = +\- 1
      // 2) delta_m1 = - delta_m2
      if(delta_m1*delta_m2 == -1.0) {
        valid = 1;
      }

      if(valid == 0) {continue;}

      // END OF SIEVE
      // If valid = 1 work out matrix element

        
      // Off diagonal term : <i |A *(1/2) [ S2+S1- + S2-S1+ ] | j>
      if( delta_m1 == -1.0) {

        // work out < m1 -1  m2 +1 | A*(1/2)[S2+S1-]| m1 m2..>
        coeff_1 = S1*(S1+1.0) - m1_j*(m1_j-1.0);
        coeff_2 = S2*(S2+1.0) - m2_j*(m2_j+1.0);
        hamiltonian.set_element( i,j, hamiltonian.get_element(i,j) + cmplxd(strength*0.5*sqrt(coeff_1*coeff_2),0.0 ) );
      
      } else {
          
          // work out < m1 +1  m2 -1 | A*(1/2)[S2-S1+]|   m1 m2..>
          coeff_1 = S1*(S1+1.0) - m1_j*(m1_j+1.0);
          coeff_2 = S2*(S2+1.0) - m2_j*(m2_j-1.0);
          hamiltonian.set_element( i,j, hamiltonian.get_element(i,j) + cmplxd(strength*0.5*sqrt(coeff_1*coeff_2),0.0)  );
        
        }
        
    }
    

  }


  return;

}

void spinHamiltonian::IsoHyperfine(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
                                            const int spin_ID_1, const int spin_ID_2, const double strength, const bool Ising_only)
                                                                                          // hyperfine
{
  if (Ising_only == 1) {
    Ising(hamiltonian, spins_in, high_field_basis, spin_ID_1, spin_ID_2, strength);
  } else {
      IsoHyperfine(hamiltonian, spins_in, high_field_basis, spin_ID_1, spin_ID_2, strength);
    }
  return;
}

//// TODO TODO TODO MAY BE INCOMPLETE + MAY BE UNSTABLE

////void spinHamiltonian::IsoHyperfine(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
////                             const int spin_ID_1, const int spin_ID_2, const double strength, const bool Ising_only,
////                             const int truncation_spin_ID_1, const int truncation_spin_ID_2,
////                             const int leaking_spin_ID) {

////  // First check if leaking spin either spin 1 or spin 2
////  if ((leaking_spin_ID != spin_ID_1) && (leaking_spin_ID != spin_ID_2)) {
////    cout << "ERROR: leaking spin must be one of the two interacting spins." << endl;
////    return;
////    exit(1);
////  }

////  // Check if leaking spin one of the "truncated spins"
////  if ((leaking_spin_ID != truncation_spin_ID_1) && (leaking_spin_ID != truncation_spin_ID_2)) {
////    cout << "ERROR: leaking spin must be one of the two spins used in truncation." << endl;
////    return;
////    exit(1);
////  }

////  // Get spin quantum numbers
////  double S1 = spins_in.get_spin_by_ID(spin_ID_1).get_spinQN_as_double();
////  double S2 = spins_in.get_spin_by_ID(spin_ID_2).get_spinQN_as_double();

////  // Dimension Hilbert space
////  int dim   = hamiltonian.dimension();

////  // Number of spins
////  int nspins = spins_in.size();

////  // Loop variables
////  int i,j,p;

////  // Magnetic quantum numbers (labeled)
////  double m1_i, m1_j; 
////  double m2_i, m2_j;
////  double m_other_i, m_other_j;

////  // Coefficients from spin raising and lowering operators
////  double coeff_1, coeff_2;
////  
////  // Test variables  
////  int valid, reject;                              
////  double delta_m1, delta_m2;

////  int l;

////      
////  // Fill matrix elements, sieving out zeros. Calculate:
////  // A S_1.S_2 = A S_1^z S_2^z + (A / 2) (S_1^+ S_2^- + S_1^- S_2^+)
////  // A: coupling strength
////  // S_1,S_2: (vector) spin operators
////  // S_1^z,S_2^z: z-component of the spin operators (magnetic field along z)
////  // S_1^+,S_1^-,S_2^+,S_2^-: spin raising and lowering operators

////  for (i=0; i<dim; i++) {
////  
////    // Calculate Ising part: A S_1^z S_2^z
////    // Matrix elements <i| H_isohyperfine |j> (i == j)
////    m1_i = high_field_basis(i,spin_ID_1);
////    m2_i = high_field_basis(i,spin_ID_2);

////    hamiltonian.set_element(i,i, hamiltonian.get_element(i,i)
////      +  cmplxd(strength*m1_i*m2_i,0.0));
////    
////    // Calculate flip-flop part: (A / 2) (S_1^+ S_2^- + S_1^- S_2^+)
////    // sieving out zeros
////    // Matrix elements <i| H_isohyperfine |j> (i != j)

////    if (Ising_only == 1) {continue;}



////    for (j=0; j<dim; j++) {


////      // Initialise test variables
////      reject     = 0;
////      valid      = 0;

////      // Off-diagonals only
////      if (i==j) {
////        continue;
////      }

////      // If the ith and jth magnetic quantum numbers differ for any of the other spins,
////      // matrix element is zero
////      for (p=0;p<nspins;p++) {
////        if ((p != spin_ID_1) && (p != spin_ID_2)) {
////          m_other_i = high_field_basis(i,p);
////          m_other_j = high_field_basis(j,p);
////          if (m_other_i != m_other_j) {
////            reject = 1;
////            break;
////          }
////        }
////      }
////      if (reject == 1) {continue;}

////      // Calculate m1_j, m2_j, delta_m1, delta_m2
////      m1_j = high_field_basis(j,spin_ID_1);
////      m2_j = high_field_basis(j,spin_ID_2);





//////      // Now check if leaking out of Hilbert space for a truncated basis
//////      valid = 0;
//////      if (leaking_spin_ID == spin_ID_1) {
//////        for (l=0;l<dim;l++) { // TODO Make faster
//////          if ( ( (m1_j + 1) == high_field_basis(l,spin_ID_1) ) && ( high_field_basis(j,truncation_spin_ID_2) == high_field_basis(l,truncation_spin_ID_2)  ) ) {
//////            valid = 1;
//////          }
//////        }
//////      } else {
//////          for (l=0;l<dim;l++) { // TODO Make faster
//////            if ( ( (m2_j + 1) == high_field_basis(l,spin_ID_2) ) && ( high_field_basis(j,truncation_spin_ID_1) == high_field_basis(l,truncation_spin_ID_1)  ) ) {
//////              valid = 1;
//////            }
//////          }
//////        }
//////      if (valid == 0) {continue;}
//////      valid = 0;


////      //cout << high_field_basis(j,1) << endl;



//////      if ((m1_j) == -0.5) {
//////        if ((high_field_basis(j,1)!=-2.5) && (high_field_basis(j,1)!=-1.5) ) {
//////          cout << "here?" << endl;
//////          continue;
//////        }
//////      }

//////      if ((m1_j) == 0.5) {
//////        if ((high_field_basis(j,1)!=-1.5) && (high_field_basis(j,1)!=-0.5) ) {
//////          cout << "or here?" << endl;
//////          continue;
//////        }
//////      }
//////    


////      // calculate delta_m1, delta_m2
////      delta_m1 = m1_i - m1_j;
////      delta_m2 = m2_i - m2_j;
////    
////      // if |delta_m1| or |delta_m2| are more than 1, reject the matrix element
////      if ( (abs(delta_m1) > 1.0) || (abs(delta_m2) > 1.0) ) {
////        continue;
////      }


////      // now test
////      // 1) delta_m = +\- 1
////      // 2) delta_m1 = - delta_m2
////      if(delta_m1*delta_m2 = -1.0) {
////        valid = 1;
////      }


////      if(valid == 0) {continue;}

////      // END OF SIEVE
////      // If valid = 1 work out matrix element

////// 0.5 -2.5
//////-0.5 -1.5
////// 0.5 -1.5
//////-0.5 -0.5

////      // suppose raising m1_j
////      // want to forbid 0.5 -0.5

////      // suppose lowering m1_j
////      // want to forbid -0.5 -2.5

////      // raise

////      if (m1_j == -0.5) {

////        if (high_field_basis(j,1)==-0.5) {
////          cout << "here?" << endl;

////          continue;
////        }
////      } else {

////        if (high_field_basis(j,1)==-2.5) {
////          cout << "or here?" << endl;
////          continue;
////        }
////      }

////            cout << "ms " << m1_j << "mBi " << high_field_basis(j,1) << endl;

//////      if (m1_j == -0.5) {
//////        if ((high_field_basis(j,1)!=-2.5) && (high_field_basis(j,1)!=-1.5) ) {
//////          continue;
//////        }
//////      } else {
//////                if ((high_field_basis(j,1)!=-1.5) && (high_field_basis(j,1)!=-0.5) ) {
//////          continue;
//////        }
//////        }

////      // Off diagonal term : <i |A *(1/2) [ S2+S1- + S2-S1+ ] | j>
////      if( delta_m1 == -1.0) {

////        // work out < m1 -1  m2 +1 | A*(1/2)[S2+S1-]| m1 m2..>
////        coeff_1 = S1*(S1+1.0) - m1_j*(m1_j-1.0);
////        coeff_2 = S2*(S2+1.0) - m2_j*(m2_j+1.0);
////        hamiltonian.set_element( i,j, hamiltonian.get_element(i,j) + cmplxd(strength*0.5*sqrt(coeff_1*coeff_2),0.0 ) );

////      
////      } else {


////          // work out < m1 +1  m2 -1 | A*(1/2)[S2-S1+]|   m1 m2..>
////          coeff_1 = S1*(S1+1.0) - m1_j*(m1_j+1.0);
////          coeff_2 = S2*(S2+1.0) - m2_j*(m2_j-1.0);
////          hamiltonian.set_element( i,j, hamiltonian.get_element(i,j) + cmplxd(strength*0.5*sqrt(coeff_1*coeff_2),0.0)  );

////        
////        }
////        
////    }
////    

////  }


////  return;

////}

//// TODO TODO TODO MAY BE INCOMPLETE + MAY BE UNSTABLE

////void spinHamiltonian::Dipolar(qoperator & hamiltonian, const spins & spins_in, const MatrixXd & high_field_basis,
////                               const int spin_ID_1, const int spin_ID_2, const double strength,const bool Ising_only,
////                             const int truncation_spin_ID_1, const int truncation_spin_ID_2,
////                             const int leaking_spin_ID)
////{

////  // First check if leaking spin either spin 1 or spin 2
////  if ((leaking_spin_ID != spin_ID_1) && (leaking_spin_ID != spin_ID_2)) {
////    cout << "ERROR: leaking spin must be one of the two interacting spins." << endl;
////    return;
////    exit(1);
////  }

////  // Check if leaking spin one of the "truncated spins"
////  if ((leaking_spin_ID != truncation_spin_ID_1) && (leaking_spin_ID != truncation_spin_ID_2)) {
////    cout << "ERROR: leaking spin must be one of the two spins used in truncation." << endl;
////    return;
////    exit(1);
////  }

////  //char switch_or_no = 'y';

////  // Get spin quantum numbers
////  double S1 = spins_in.get_spin_by_ID(spin_ID_1).get_spinQN_as_double();
////  double S2 = spins_in.get_spin_by_ID(spin_ID_2).get_spinQN_as_double();

////  // Dimension Hilbert space
////  int dim = hamiltonian.dimension();

////  // Number of spins
////  int nspins = spins_in.size();

////  // Loop variables
////  int i,j,p;

////  // Magnetic quantum numbers (labeled)
////  double m1_i, m1_j; 
////  double m2_i, m2_j;
////  double m_other_i, m_other_j;

////  // Coefficients from spin raising and lowering operators
////  double coeff_1, coeff_2;
////  
////  // Test variables  
////  int valid, reject;                              
////  double delta_m1, delta_m2;

////  int l;
////  
////      
////  // Fill matrix elements, sieving out zeros. Calculate:
////  // D S_1^z S_2^z - (D / 4) (S_1^+ S_2^- + S_1^- S_2^+)
////  // D: dipolar coupling strength
////  // S_1,S_2: (vector) spin operators
////  // S_1^z,S_2^z: z-component of the spin operators (magnetic field along z)
////  // S_1^+,S_1^-,S_2^+,S_2^-: spin raising and lowering operators

////  for (i=0; i<dim; i++) {
////  
////    // Calculate Ising part: D S_1^z S_2^z
////    // Matrix elements <i| H_dipolar |j> (i == j)
////    m1_i = high_field_basis(i,spin_ID_1);
////    m2_i = high_field_basis(i,spin_ID_2);

////    hamiltonian.set_element( i, i, hamiltonian.get_element(i,i)
////      +  cmplxd(strength*m1_i*m2_i,0.0) );

////    if (Ising_only == 1){continue;}
////    
////    // Calculate flip-flop part: - (D / 4) (S_1^+ S_2^- + S_1^- S_2^+)
////    // sieving out zeros
////    // Matrix elements <i| H_dipolar |j> (i != j)
////    for (j=0; j<dim; j++) {
////    
////      // Initialise test variables
////      reject     = 0;
////      valid      = 0;

////      // Off-diagonals only
////      if (i==j) {
////        continue;
////      }

////      // If the ith and jth magnetic quantum numbers differ for any of the other spins,
////      // matrix element is zero
////      for (p=0;p<nspins;p++) {
////        if ((p != spin_ID_1) && (p != spin_ID_2)) {
////          m_other_i = high_field_basis(i,p);
////          m_other_j = high_field_basis(j,p);
////          if (m_other_i != m_other_j) {
////            reject = 1;
////            break;
////          }
////        }
////      }
////      if (reject == 1) {continue;}

////      // Calculate m1_j, m2_j, delta_m1, delta_m2
////      m1_j = high_field_basis(j,spin_ID_1);
////      m2_j = high_field_basis(j,spin_ID_2);

////      // Now check if leaking out of Hilbert space for a truncated basis

////      valid = 0;

////      if (leaking_spin_ID == spin_ID_1) {
////        for (l=0;l<dim;l++) { // TODO Make faster
////          if ( ( (m1_j + 1) == high_field_basis(l,spin_ID_1) ) && ( high_field_basis(j,truncation_spin_ID_2) == high_field_basis(l,truncation_spin_ID_2)  ) ) {
////            valid = 1;
////          }
////        }
////      } else {

////          for (l=0;l<dim;l++) { // TODO Make faster
////            if ( ( (m2_j + 1) == high_field_basis(l,spin_ID_2) ) && ( high_field_basis(j,truncation_spin_ID_1) == high_field_basis(l,truncation_spin_ID_1)  ) ) {
////              valid = 1;
////            }
////          }

////        }

////      if (valid == 0) {continue;}

////      valid = 0;

////      delta_m1 = m1_i - m1_j;
////      delta_m2 = m2_i - m2_j;
////      
////    
////      // if |delta_m1| or |delta_m2| are more than 1, reject the matrix element
////      if ( (abs(delta_m1) > 1.0) || (abs(delta_m2) > 1.0) ) {
////        continue;
////      }
////      
////      // now test
////      // 1) delta_m = +\- 1
////      // 2) delta_m1 = - delta_m2
////      if(delta_m1*delta_m2 == -1.0) {
////        valid = 1;
////      }

////      if(valid == 0) {continue;}

////      // END OF SIEVE
////      // If valid = 1 work out matrix element

//////      cout << "Change?" <<  endl;
//////      cin >> switch_or_no;
//////      if (switch_or_no == 'y') {
//////        delta_m1 = -1.0;
//////        cout << "changed" << endl;
//////      } else {
//////          cout << "not changed" << endl;
//////        }

////      // Off diagonal term : - <i |D *(1/4) [ S2+S1- + S2-S1+ ] | j>
////      if( delta_m1 == -1.0) {
////        // work out - < m1 -1  m2 +1 | D*(1/4)[S2+S1-]| m1 m2..>
////        coeff_1 = S1*(S1+1.0) - m1_j*(m1_j-1.0);
////        coeff_2 = S2*(S2+1.0) - m2_j*(m2_j+1.0);
////        hamiltonian.set_element(i,j, hamiltonian.get_element(i,j) - cmplxd(strength*0.25*sqrt(coeff_1*coeff_2),0.0 ) );
////      
////      } else {
////          
////          // work out < m1 +1  m2 -1 | A*(1/2)[S2-S1+]|   m1 m2..>
////          coeff_1 = S1*(S1+1.0) - m1_j*(m1_j+1.0);
////          coeff_2 = S2*(S2+1.0) - m2_j*(m2_j-1.0);
////          hamiltonian.set_element( i,j,hamiltonian.get_element(i,j) - cmplxd(strength*0.25*sqrt(coeff_1*coeff_2),0.0 ) );
////        
////        }
////        
////    }
////    

////  }


////  return;

////}




void spinHamiltonian::Zeeman(qoperator & hamiltonian, const spins & spins_in, const MatrixXd high_field_basis,
                                     const double magnetic_field)
{
  // Get the number of spins
  int nspins = spins_in.size();

  // Get the dimension of the Hilbert space
  int dim = hamiltonian.dimension();
  
  int i,p;

  // Fill the diagonals
  for (i=0; i<dim; i++) {
    for (p=0; p<nspins; p++) {
      hamiltonian.set_element( i,i, hamiltonian.get_element(i,i)
      + cmplxd(magnetic_field*spins_in.get_spin_by_ID(p).get_gyromagneticRatio()*high_field_basis(i,p),0.0 ));
    }
  }
  
  return;

}




