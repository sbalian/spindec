#ifndef REDUCEDPROBLEM_H_
#define REDUCEDPROBLEM_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinSystemBase.h"

namespace SpinDec
{

/// SpinSystemBase and an order.
class ReducedProblem
{
private:
  
  UInt order_;
  shared_ptr<SpinSystemBase> spin_system_base_;
  
public:
  
  ReducedProblem();
  ReducedProblem(const UInt order,
      const shared_ptr<SpinSystemBase>& spin_system_base);
  
  ReducedProblem(const ReducedProblem& rhs);
  ReducedProblem& operator=(const ReducedProblem& rhs);
  
  UInt get_order() const;
  shared_ptr<SpinSystemBase> get_spin_system() const;

  
};

} // namespace SpinDec

#endif // REDUCEDPROBLEM_H_
