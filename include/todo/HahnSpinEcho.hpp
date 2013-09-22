#ifndef HAHNSPINECHO_H
#define HAHNSPINECHO_H

// Hahn spin echo sequence
// unitary time evolution - pi-pulse - unitary time evolution
//
// Created  06/06/2012
// Modified 20/09/2012, 01/11/2012, 29/11/2012
// Modified 02/12/2012 - complex echo
// Modified 03/12/2012
// Modified 10/01/2013 - added norm
// Modified 18/01/2013 - added abs return
// Seto Balian
// V1

// NOTE: Needs commenting

#include "stdincludes.hpp"
#include "qoperator.hpp"
#include "statevector.hpp"

class HahnSpinEcho
{

public:

  static cmplxd calculate(const cmplxd & norm, const qoperator & U, const qoperator & PIPULSE, const statevector & ISTATE, const int BATHDIM, const statevector & LEVEL0, const statevector & LEVEL1, const bool abs_echo);

  static cmplxd calculate(const cmplxd & norm, const qoperator & U, const qoperator & PIPULSE, const statevector & ISTATE, const int BATHDIM, const statevector & LEVEL0, const statevector & LEVEL1);

  static cmplxd calculate(const cmplxd & norm, const qoperator & U, const statevector & ISTATE, const int BATHDIM, const statevector & LEVEL0, const statevector & LEVEL1);

//  static cmplxd calculate(const qoperator & U, const qoperator & PIPULSE, const statevector & ISTATE, const vector<statevector> & TRACER0, const vector<statevector> & TRACER1);

};

#endif // HAHNSPINECHO_H

