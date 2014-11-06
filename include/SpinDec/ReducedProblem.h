#ifndef REDUCEDPROBLEM_H_
#define REDUCEDPROBLEM_H_

// SpinDec::ReducedProblem
//
// SpinSystemBase and an order.
//
// Seto Balian, Nov 6, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinSystemBase.h"

namespace SpinDec
{

class ReducedProblem
{
private:
  
  UInt order_;
  auto_ptr<SpinSystemBase> spin_system_base_;
  
public:
  
  ReducedProblem();
  ReducedProblem(const UInt order,
      const auto_ptr<SpinSystemBase>& spin_system_base);
  
  ReducedProblem(const ReducedProblem& rhs);
  ReducedProblem& operator=(const ReducedProblem& rhs);
  
  UInt get_order() const;
  auto_ptr<SpinSystemBase> get_spin_system() const;

  
};

} // namespace SpinDec

#endif // REDUCEDPROBLEM_H_
