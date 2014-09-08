#ifndef PULSEEXPERIMENT_H_
#define PULSEEXPERIMENT_H_

// SpinDec::PulseExperiment
//
// Abstract base class for a pulse sequence experiment.
//
// Seto Balian, Sep 8, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/TimeArray.h"
#include "SpinDec/CSDProblem.h"
#include "SpinDec/TimeEvolution.h"

namespace SpinDec
{

class PulseExperiment
{
protected:
  
  CSDProblem csd_problem_;
  TimeArray time_array_;
  
public:
  PulseExperiment();
  PulseExperiment(const CSDProblem& csd_problem,
      const TimeArray& time_array);
  
  virtual TimeEvolution time_evolution(const UIntArray bath_indices) = 0;
  
  virtual std::auto_ptr<PulseExperiment> clone() const = 0;
  
  const TimeArray& get_time_array() const;
  
  virtual ~PulseExperiment();
  
};

} // namespace SpinDec

#endif // PULSEEXPERIMENT_H_
