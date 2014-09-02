#ifndef PULSEEXPERIMENT_H_
#define PULSEEXPERIMENT_H_

// SpinDec::PulseExperiment
//
// Experiment with a pulse sequence. TODO Comment
//
// Seto Balian, Sep 2, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/PulseSequence.h"
#include "SpinDec/TimeEvolution.h"
#include "SpinDec/TimeArray.h"

namespace SpinDec
{

class PulseExperiment
{
  
protected:
  
  std::auto_ptr<PulseSequence> pulse_sequence_;
  TimeArray time_array_;
  
public:
  PulseExperiment();

  PulseExperiment(const PulseExperiment& other);
  PulseExperiment& operator=( const PulseExperiment& other);

  PulseExperiment(const auto_ptr<PulseSequence>& pulse_sequence,
      const TimeArray& time_array);
  
  virtual TimeEvolution time_evolution(const double time,
      const SpinState& initial_state) = 0;
  
  virtual std::auto_ptr<PulseExperiment> clone() const = 0;
  
  virtual ~PulseExperiment();
  
};

} // namespace SpinDec

#endif // PULSEEXPERIMENT_H_
