// See FreeEvolution.h for description.
// Seto Balian, Sep 2, 2014

#include "SpinDec/FreeEvolution.h"

namespace SpinDec
{

FreeEvolution::FreeEvolution()
{
}

FreeEvolution::FreeEvolution(
    const EvolutionOperator& evolution_operator) :
        Pulse(evolution_operator.get_time(),
            SpinOperator( evolution_operator.get_matrix(),
                  evolution_operator.get_basis()))
{
}

} // namespace SpinDec

