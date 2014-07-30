#ifndef CPMG_H_
#define CPMG_H_

// SpinDec::CPMG
//
// Carr-Purcell-Meiboom-Gill (CPMG) pulse sequence.
//
// Seto Balian, Jul 30, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/PulseSequence.h"
#include "SpinDec/PiPulse.h"
#include "SpinDec/SpinHamiltonian.h"

namespace SpinDec
{

class CPMG : public PulseSequence
{
private:
  PiPulse pi_pulse_;
  UInt order_;
  double time_gap_;
  SpinHamiltonian hamiltonian_;
  ComplexMatrix eigenvectors_;
  RealVector eigenvalues_;
  
public:
  
  CPMG();
  CPMG(const UInt order,
       const double duration,
       const SpinState & state0, const SpinState & state1,
       const vector<SpinState> & other_states,
       const vector<SpinState>& unaffected_states,
       const SpinHamiltonian& hamiltonian,
       const ComplexMatrix& eigenvectors,
       const RealVector& eigenvalues);
  
  virtual void calculate(const SpinState& initial_state,
       const double duration);
  
};

} // namespace SpinDec

#endif // CPMG_H_
