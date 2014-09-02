// See CPMGExperiment.h for description.
// Seto Balian, Sep 2, 2014

#include "SpinDec/CPMGExperiment.h"
#include "SpinDec/DensityOperator.h"

namespace SpinDec
{

CPMGExperiment::CPMGExperiment()
{
}

CPMGExperiment::CPMGExperiment(const CPMG& cpmg,
    const TimeArray& time_array) :
        PulseExperiment(cpmg.clone(),time_array)
{
  state0_ = cpmg.get_state0();
  state1_ = cpmg.get_state1();

}


TimeEvolution CPMGExperiment::time_evolution(const double time,
    const SpinState& initial_state)
{
  pulse_sequence_->set_initial_state(initial_state);
  
  // CPMG coherence
  CDoubleArray L;
  
  CDouble norm = CDouble(1.0,0.0);
  
  for (UInt i=0;i<time_array_.get_dimension();i++) {
    
    // calculate the pulse sequence
    pulse_sequence_->update( time_array_.get_time(i) );

    SpinState final_state = pulse_sequence_->final_state();
    
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
  return TimeEvolution(time_array_,L);
  
}

std::auto_ptr<PulseExperiment> CPMGExperiment::clone() const
{
  return std::auto_ptr<PulseExperiment>( new CPMGExperiment(*this) );
}

} // namespace SpinDec

