// Hahn spin echo sequence
// unitary time evolution - pi-pulse - unitary time evolution
//
// Created  06/06/2012
// Modified 20/09/2012, 22/09/2012, 28/09/2012, 01/11/2012, 20/11/2012, 24/11/2012, 29/11/2012
// Modified 02/12/2012 - complex echo
// Modified 03/12/2012
// Modified 10/01/2013 - added norm
// Modified 15/01/2013
// Modified 17/01/2013
// Modified 18/01/2013 - added abs return
// Modified 16/05/2013
// Seto Balian
// V1

// NOTE: Needs commenting

#include "stdincludes.hpp"
#include "HahnSpinEcho.hpp"
#include "qoperator.hpp"
#include "statevector.hpp"

using namespace std;

cmplxd HahnSpinEcho::calculate(const cmplxd & norm, const qoperator & U, const qoperator & PIPULSE, const statevector & ISTATE, const int BATHDIM, const statevector & LEVEL0, const statevector & LEVEL1, const bool abs_echo) {

//  cout << setprecision(8) << left << scientific;
//  cout << "Norm before U: " << ISTATE.mod() << " ";

//  statevector FSTATE = U*ISTATE;

//  cout << "Norm after  U: " << FSTATE.mod() << " ";

//  FSTATE = PIPULSE*FSTATE;

//  cout << "Norm after PI: " << FSTATE.mod() << " ";

//  FSTATE = U*FSTATE;

//  cout << "Norm after  U: " << FSTATE.mod() << endl;

  statevector FSTATE = U*(PIPULSE*(U*ISTATE));
  // FSTATE = FSTATE.normalised();

  qoperator FDENS    = qoperator(FSTATE,FSTATE);
  FDENS = FDENS.partial_trace(BATHDIM);

  if (abs_echo == 0) {
    return (cmplxd(1.0,0.0)/norm)*(LEVEL0*(FDENS*LEVEL1));
  } else {
      return cmplxd( abs( (cmplxd(1.0,0.0)/norm)*(LEVEL0*(FDENS*LEVEL1)) ) ,0.0);
    }
}

cmplxd HahnSpinEcho::calculate(const cmplxd & norm, const qoperator & U, const qoperator & PIPULSE, const statevector & ISTATE, const int BATHDIM, const statevector & LEVEL0, const statevector & LEVEL1) {

  return HahnSpinEcho::calculate(norm,U,PIPULSE,ISTATE,BATHDIM,LEVEL0,LEVEL1,0);

}


cmplxd HahnSpinEcho::calculate(const cmplxd & norm, const qoperator & U, const statevector & ISTATE, const int BATHDIM, const statevector & LEVEL0, const statevector & LEVEL1) {

  statevector FSTATE = U*ISTATE;

//  FSTATE = FSTATE.normalised();
  qoperator FDENS    = qoperator(FSTATE,FSTATE);
  FDENS = FDENS.partial_trace(BATHDIM);
  return (cmplxd(1.0,0.0)/norm)*(LEVEL0*(FDENS*LEVEL1));

}


//cmplxd HahnSpinEcho::calculate(const qoperator & U, const qoperator & PIPULSE, const statevector & ISTATE, const vector<statevector> & TRACER0, const vector<statevector> & TRACER1) {

//  statevector FSTATE = U*(PIPULSE*(U*ISTATE));
////  FSTATE = FSTATE.normalised();
//  qoperator FDENS = qoperator(FSTATE,FSTATE);
////  MatrixXcd zeros(FSTATE.dimension(),FSTATE.dimension());
////  MatrixXcd zeros(FSTATE.dimension(),FSTATE.dimension());
//  cmplxd echointensity = cmplxd(0.0,0.0);
//  cmplxd temp          = cmplxd(0.0,0.0);

//  VectorXcd tr_1;
//  RowVectorXcd tr_0;
//  MatrixXcd P = FDENS.get_matrix_rep();

//  int i;
//  for (i=0;i<int(TRACER0.size());i++) {
//    tr_0 = TRACER0[i].get_row_vec();
//    tr_1 = TRACER1[i].get_col_vec();

//    temp = tr_0*(P*tr_1);
//    echointensity = echointensity + temp;

////    echointensity = cmplxd( echointensity.real() + temp.real()  , echointensity.imag() + temp.imag() );
//    
//  }

//  return cmplxd(2.0,0.0)*(echointensity);

//}


