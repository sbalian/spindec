// See PulseExperiment.h for description.
// Seto Balian, Sep 8, 2014

#include "SpinDec/PulseExperiment.h"

namespace SpinDec
{

PulseExperiment::PulseExperiment()
{
}

PulseExperiment::PulseExperiment(
    const CSDProblem& csd_problem, const TimeArray& time_array)
{
  time_array_ = time_array;
  csd_problem_ = csd_problem;
}

const TimeArray& SpinDec::PulseExperiment::get_time_array() const
{
  return time_array_;
}

PulseExperiment::~PulseExperiment()
{
}


} // namespace SpinDec

