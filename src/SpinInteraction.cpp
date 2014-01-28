// See SpinInteraction.h for description.
// Seto Balian, Jan 28, 2014

#include "SpinInteraction.h"

SpinInteraction::SpinInteraction() :
  spin1_(Spin()),
  spin2_(Spin())
{
  strength_ = 0.0;
  non_spatial_dependence_ = 0.0;
}

SpinInteraction::SpinInteraction(const Spin& spin1, const Spin& spin2) :
    spin1_(spin1),
    spin2_(spin2)
{
  strength_ = 0.0;
  non_spatial_dependence_ = 0.0;
}

SpinInteraction::SpinInteraction(const Spin& spin1, const Spin& spin2,
    const double strength) :
    spin1_(spin1),
    spin2_(spin2)
{
  strength_ = strength;
  non_spatial_dependence_ = 0.0;
}

double SpinInteraction::get_strength() const
{
  return strength_;
}


void SpinInteraction::set_strength(const double strength)
{
  strength_ = strength;
  return;
}

SpinInteraction::~SpinInteraction()
{/**/
}

void SpinInteraction::fill_ising_flipflop(Eigen::MatrixXcd& hamiltonian,
    const SpinVector& spins, const Eigen::ArrayXXd& basis,
    const unsigned int spin_label1, const unsigned int spin_label2,
    const bool ising_only, const std::complex<double> & flipflop_form) const
{

  // Get spin quantum numbers
  const double S1 = spins[spin_label1].get_quantum_number();
  const double S2 = spins[spin_label2].get_quantum_number();
  
  // Dimension of Hilbert space
  const unsigned int dimension = hamiltonian.rows();
  
  // Number of spins
  const unsigned int nspins = spins.size();
  
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
  
  for (unsigned int i=0; i< dimension; i++) {
  
    // Calculate Ising part: D S_1^z S_2^z
    // Matrix elements <i| H_dipolar |j> (i == j)
    m1_i = basis(i,spin_label1);
    m2_i = basis(i,spin_label2);
    
    hamiltonian(i,i) += std::complex<double>(get_strength()*m1_i*m2_i,0.0);
    
    // Only fill diagonals for Ising only
    if (ising_only) {continue;}
    
    // Calculate flip-flop part: D F (S_1^+ S_2^- + S_1^- S_2^+)
    // sieving out zeros
    // Matrix elements <i| H_dipolar |j> (i != j)
    for (unsigned int j=0; j<dimension; j++) {
    
      // Initialise test variables
      reject     = 0;
      valid      = 0;
  
      // Off-diagonals only
      if (i==j) {
        continue;
      }
  
      // If the ith and jth magnetic quantum numbers differ for any of the
      // other spins, matrix element is zero
      for (unsigned int p=0;p<nspins;p++) {
        if ((p != spin_label1) && (p != spin_label2)) {
          m_other_i = basis(i,p);
          m_other_j = basis(j,p);
          if (m_other_i != m_other_j) {
            reject = 1;
            break;
          }
        }
      }
      if (reject == 1) {continue;}
  
      // Calculate m1_j, m2_j, delta_m1, delta_m2
      m1_j = basis(j,spin_label1);
      m2_j = basis(j,spin_label2);
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
      
      hamiltonian(i,j) +=
      std::complex<double>(get_strength()*
                  std::sqrt(static_cast<long double>(coeff_1*coeff_2)),0.0)*
                  flipflop_form;
        
    }
    
  
  }
  return;

}
