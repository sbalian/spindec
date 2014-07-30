// See CPMG.h for description.
// Seto Balian, Jul 30, 2014

#include "SpinDec/CPMG.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

CPMG::CPMG() : order_(0),time_gap_(0.0)
{
}

CPMG::CPMG(const UInt order,
    const double duration, const SpinState& state0, const SpinState& state1,
    const vector<SpinState>& other_states,
    const vector<SpinState>& unaffected_states,
    const SpinHamiltonian& hamiltonian,
    const ComplexMatrix& eigenvectors,
    const RealVector& eigenvalues) :
      PulseSequence(SpinState(),duration)
{
  order_ = order;
  
  // Time before and after a pi pulse
  if (order_ == 0) { // FID
    time_gap_ = duration_;
  } else { // Hahn (CPMG-1), CPMG-2, CPMG-3, ...
    time_gap_ = duration_/(2.0*static_cast<double>(order));
  }
  
  // construct the pi pulse
  pi_pulse_ = PiPulse(state0,state1,other_states,unaffected_states);
  hamiltonian_ = hamiltonian;
  eigenvectors_ = eigenvectors;
  eigenvalues_ = eigenvalues;
  
  // TODO more checks like this in other classes
  // check eigenvalue and eigenvector dimensions
  if (eigenvectors.rows() != eigenvectors.cols()) {
    Errors::quit("Eigenvectors matrix is not square.");
  }
  
  if (eigenvectors.rows() != hamiltonian_.get_dimension()) {
    Errors::quit("Eigenvector dimension incorrect.");
  }
  
  if (eigenvalues.rows() != hamiltonian_.get_dimension()) {
    Errors::quit("Number of eigenvalues incorrect.");
  }
  
}

void CPMG::calculate(const SpinState& initial_state,
    const double duration)
{
  
  initial_state_ = initial_state;
  
  // check if initial state and pi pulse have the same bases
  if (!(initial_state_.get_basis().is_equal(hamiltonian_.get_basis()))) {
    Errors::quit("Initial state and Hamiltonian do not have the same basis.");
  }
  
  ComplexMatrix evolution_matrix =
      hamiltonian_.evolution_matrix(
              eigenvectors_,eigenvalues_,time_gap_);
  
  ComplexMatrix pi_pulse_matrix = pi_pulse_.get_pulse_operator().get_matrix();
  
  //FID
  if (order_ == 0) {
    final_state_.set_state_vector(
        initial_state_.get_state_vector()*evolution_matrix  );
  } else {
    // Hahn (CPMG-1), CPMG-2, CPMG-3, ...
    final_state_.set_state_vector(initial_state_.get_state_vector());
    ComplexVector final_state_vector = final_state_.get_state_vector();
    
    for (UInt i=0;i<order_;i++) {

      final_state_vector = evolution_matrix*final_state_vector;
      final_state_vector = pi_pulse_matrix*final_state_vector;
      final_state_vector = evolution_matrix*final_state_vector;
    }
  }
  return;
}


} // namespace SpinDec

