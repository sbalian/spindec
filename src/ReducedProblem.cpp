// See ReducedProblem.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/ReducedProblem.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

ReducedProblem::ReducedProblem() : order_(0)
{
}

ReducedProblem::ReducedProblem(const UInt order,
    const shared_ptr<SpinSystemBase>& spin_system_base)
:order_(order),
 spin_system_base_(spin_system_base->clone())
{
  if (order_ == 0) {
    Errors::quit("Order must be at least 1.");
  }
}

ReducedProblem::ReducedProblem(const ReducedProblem& rhs)
{
  *this = rhs;
}

ReducedProblem& ReducedProblem::operator =(const ReducedProblem& rhs)
{
  order_ = rhs.order_;
  spin_system_base_=rhs.spin_system_base_->clone();
  return *this;
}

UInt ReducedProblem::get_order() const
{
  return order_;
}

shared_ptr<SpinSystemBase> ReducedProblem::get_spin_system() const
{
  return spin_system_base_->clone();
}


} // namespace SpinDec

