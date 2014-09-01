// See FreeEvolution.h for description.
// Seto Balian, Sep 1, 2014

#include "SpinDec/FreeEvolution.h"

namespace SpinDec
{

void FreeEvolution::construct_pulse_operator()
{
  pulse_operator_ = SpinOperator( evolution_operator_.get_matrix(),
      evolution_operator_.get_basis());
}

FreeEvolution::FreeEvolution()
{
}

FreeEvolution::FreeEvolution(
    const EvolutionOperator& evolution_operator) :
        Pulse(evolution_operator.get_time()),
        evolution_operator_(evolution_operator)
{
  
}

std::auto_ptr<Pulse> FreeEvolution::clone() const
{
  return std::auto_ptr<Pulse>( new FreeEvolution(*this) );
}


} // namespace SpinDec

