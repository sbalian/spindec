// See CPMG.h for description.
// Seto Balian, Aug 4, 2014

#include "SpinDec/CPMG.h"
#include "SpinDec/Errors.h"
#include "SpinDec/DensityOperator.h"

namespace SpinDec
{

CPMG::CPMG() : order_(0),time_gap_(0.0),is_pi_pulse_constructed_(false)
{
}

CPMG::CPMG(const UInt order, const SpinState& state0, const SpinState& state1,
    const std::auto_ptr<SpinSystemBase> & spin_system_base) :
      PulseSequence()
{
  
  is_pi_pulse_constructed_ = false;
  order_ = order;
  
  time_gap_ = 0.0;
  duration_ = 0.0;
  
  state0_ = state0;
  state1_ = state1;
  
  
  hamiltonian_ = spin_system_base->get_hamiltonian();
  eigenvectors_ = spin_system_base->get_eigenvector_matrix();
  eigenvalues_ = spin_system_base->get_eigenvalue_vector();

}

CPMG::CPMG(const UInt order, const UInt lower_donor_level,
    const UInt upper_donor_level, const SpinDonor& spin_donor,
    const SpinSystem& combined_spin_system) :
        PulseSequence()
{
  is_pi_pulse_constructed_ = false;
  order_ = order;
  
  time_gap_ = 0.0;
  duration_ = 0.0;
  
  state0_ = spin_donor.eigenstate(lower_donor_level);
  state1_ = spin_donor.eigenstate(upper_donor_level);
  
  UIntArray orthogonal_level_labels = spin_donor.get_orthogonal_level_labels();
  for (UInt i=0;i<orthogonal_level_labels.size();i++) {
    add_other_state(
        spin_donor.eigenstate(orthogonal_level_labels[i]));
  }
  
  hamiltonian_ = combined_spin_system.get_hamiltonian();
  eigenvectors_ = combined_spin_system.get_eigenvector_matrix();
  eigenvalues_ = combined_spin_system.get_eigenvalue_vector();

}


void CPMG::add_other_state(const SpinState& other_state)
{
  if (is_pi_pulse_constructed_ == true) {
    Errors::quit("Can't add other state if pi pulse already constructed");
  }
  other_states_.push_back(other_state);
  return;
}

void CPMG::add_state_to_trace_out(const SpinState& state_to_trace_out)
{
  if (is_pi_pulse_constructed_ == true) {
    Errors::quit("Can't add unaffected state if pi pulse already constructed");
  }
  states_to_trace_out_.push_back(state_to_trace_out);
  return;
}

void CPMG::calculate(const SpinState& initial_state,
    const double duration)
{
  
  // construct the pi pulse
  if (is_pi_pulse_constructed_ == false) {
    pi_pulse_ = PiPulse(state0_,state1_,other_states_,states_to_trace_out_);
    is_pi_pulse_constructed_ = true;
  }
  
  duration_ = duration;
  
  // Time before and after a pi pulse
  if (order_ == 0) { // FID
    time_gap_ = duration_;
  } else { // Hahn (CPMG-1), CPMG-2, CPMG-3, ...
    time_gap_ = duration_/(2.0*static_cast<double>(order_));
  }

  initial_state_ = initial_state;
    
  // check if initial state and pi pulse have the same bases
  if (!(initial_state_.get_basis().is_equal(hamiltonian_.get_basis()))) {
    Errors::quit("Initial state and Hamiltonian do not have the same basis.");
  }
  
  ComplexMatrix evolution_matrix =
      hamiltonian_.evolution_matrix(
              eigenvectors_,eigenvalues_,time_gap_);
  SpinOperator evolution_operator(evolution_matrix,hamiltonian_.get_basis());
  SpinOperator pi_pulse_operator = pi_pulse_.get_pulse_operator();

  
  //FID
  if (order_ == 0) {
    final_state_ = evolution_operator*initial_state_;
  } else {
    // Hahn (CPMG-1), CPMG-2, CPMG-3, ...
    final_state_ = initial_state_;
    
    for (UInt i=0;i<order_;i++) {

      final_state_ = evolution_operator*final_state_;
      final_state_ = pi_pulse_operator*final_state_;
      final_state_ = evolution_operator*final_state_;
      
    }
  }
  

  
  return;
}

CDouble CPMG::decay_experiment(const SpinState& initial_state,
     const double duration)
{
  TimeArray single_time = TimeArray(duration);
  CDoubleArray  L = decay_experiment(initial_state,single_time);
  return L[0];
}

CDoubleArray CPMG::decay_experiment(const SpinState& initial_state,
    const TimeArray& time_array)
{
  // Hahn spin echo decay
  CDoubleArray L;
  
  CDouble norm = CDouble(1.0,0.0);
  for (UInt i=0;i<time_array.get_dimension();i++) {
    
    // calculate the pulse sequence
    calculate(initial_state,time_array.get_time(i));
    SpinState final_state = get_final_state();
    DensityOperator density_operator(final_state,
        state0_,
        state1_);
    // off diagonal of reduced density matrix
    if (i==0) { // norm
      norm = density_operator.off_diagonal_reduced();
      L.push_back(CDouble(1.0,0.0));
    } else {
      L.push_back( density_operator.off_diagonal_reduced()/norm );
    }
    
    
  }
  
  return L;

}

} // namespace SpinDec

