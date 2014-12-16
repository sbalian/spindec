// See SpinInteraction.h for description.
// Seto Balian, Dec 8, 2014

#include "SpinDec/SpinInteraction.h"
#include "SpinDec/Errors.h"
#include <cmath>

namespace SpinDec
{

SpinInteraction::SpinInteraction() :
  strength_(0.0),
  strength_preset_(false)
{
}

SpinInteraction::SpinInteraction(const double strength) :
  strength_(strength),
  strength_preset_(true)
{
}

SpinInteraction::~SpinInteraction()
{/**/}

void SpinInteraction::fill_ising_flipflop(ComplexMatrix * hamiltonian,
    const SpinParametersVector& spin_parameters_vector, const SpinBasis & basis,
    const UInt spin_label1, const UInt spin_label2,
    const bool ising_only, const CDouble & flipflop_form) const
{

  // Get spin quantum numbers
  const double S1 = spin_parameters_vector[spin_label1].get_quantum_number();
  const double S2 = spin_parameters_vector[spin_label2].get_quantum_number();
  
  // Dimension of Hilbert space
  const UInt dimension = hamiltonian->rows();
  
  // Number of spins
  const UInt nspins = spin_parameters_vector.size();
  
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
  // D S_1^z S_2^z + D F (S_1^+ S_2^- + S_1^- S_2^+)
  // D: coupling strength
  // F: complex number (flipflop_form)
  // S_1,S_2: (vector) spin operators
  // S_1^z,S_2^z: z-component of the spin operators (magnetic field along z)
  // S_1^+,S_1^-,S_2^+,S_2^-: spin raising and lowering operators
  
  for (UInt i=0; i< dimension; i++) {
  
    // Calculate Ising part: D S_1^z S_2^z
    // Matrix elements <i| H_dipolar |j> (i == j)
    m1_i = basis.get_element(i,spin_label1);
    m2_i = basis.get_element(i,spin_label2);
    
    (*hamiltonian)(i,i) += CDouble(get_strength()*m1_i*m2_i,0.0);
    
    // Only fill diagonals for Ising only
    if (ising_only)
    {
      continue;
    }
    
    // Calculate flip-flop part: D F (S_1^+ S_2^- + S_1^- S_2^+)
    // sieving out zeros
    // Matrix elements <i| H_dipolar |j> (i != j)
    for (UInt j=0; j<dimension; j++) {
    
      // Initialise test variables
      reject     = 0;
      valid      = 0;
  
      // Off-diagonals only
      if (i==j) {
        continue;
      }
  
      // If the ith and jth magnetic quantum numbers differ for any of the
      // other spins, matrix element is zero
      for (UInt p=0;p<nspins;p++) {
        if ((p != spin_label1) && (p != spin_label2)) {
          m_other_i = basis.get_element(i,p);
          m_other_j = basis.get_element(j,p);
          if (m_other_i != m_other_j) {
            reject = 1;
            break;
          }
        }
      }
      if (reject == 1) {continue;}
  
      // Calculate m1_j, m2_j, delta_m1, delta_m2
      m1_j = basis.get_element(j,spin_label1);
      m2_j = basis.get_element(j,spin_label2);
      delta_m1 = m1_i - m1_j;
      delta_m2 = m2_i - m2_j;
    
      // if |delta_m1| or |delta_m2| are more than 1, reject the matrix
      // element
      if ( (std::abs(delta_m1) > 1.0) || (std::abs(delta_m2) > 1.0) ) {
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
  
      // Off diagonal term :  <i |D F [ S2+S1- + S2-S1+ ] | j>
      if( delta_m1 == -1.0) {
        // work out  < m1 -1  m2 +1 | D*F[S2+S1-]| m1 m2..>
        coeff_1 = S1*(S1+1.0) - m1_j*(m1_j-1.0);
        coeff_2 = S2*(S2+1.0) - m2_j*(m2_j+1.0);
        
      } else {
          
          // work out < m1 +1  m2 -1 | D*F*[S2-S1+]|   m1 m2..>
          coeff_1 = S1*(S1+1.0) - m1_j*(m1_j+1.0);
          coeff_2 = S2*(S2+1.0) - m2_j*(m2_j-1.0);
        }
      
      (*hamiltonian)(i,j) +=
      CDouble(get_strength()*
                  std::sqrt(coeff_1*coeff_2),0.0)*
                  flipflop_form;
        
    }
    
  
  }
  return;

}

void SpinInteraction::warn_if_preset_then_calculated() const
{
  Errors::warning("Calculating a preset spin interaction.");
  return;
}

bool SpinInteraction::strength_preset() const
{
  return strength_preset_;
}

double SpinInteraction::get_strength() const
{
  return strength_;
}

} // namespace SpinDec

