#ifndef ERRORS_H_
#define ERRORS_H_

// Errors
//
// Error and warning handling.
//
// Seto Balian, Mar 24, 2014

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class Errors
{

public:

  static void quit();
  static void quit(const string & message);
  static void warning(const string & message);

};

} // namespace SpinDec

#endif // ERRORS_H_
