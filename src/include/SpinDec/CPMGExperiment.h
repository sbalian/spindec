#ifndef CPMGEXPERIMENT_H_
#define CPMGEXPERIMENT_H_

// SpinDec::CPMGExperiment
//
// CPMG Pulse experiment. TODO Comment
//
// Seto Balian, Sep 2, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/PulseExperiment.h"
#include "SpinDec/CPMG.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

class CPMGExperiment : public PulseExperiment
{
private:
  SpinState state0_;
  SpinState state1_;
  
public:
  
  CPMGExperiment();
  CPMGExperiment(const CPMG& cpmg,const TimeArray& time_array);
  
  virtual TimeEvolution time_evolution(const double time,
                                       const SpinState& initial_state);
  
  virtual std::auto_ptr<PulseExperiment> clone() const;
  
};

} // namespace SpinDec

#endif // CPMGEXPERIMENT_H_
