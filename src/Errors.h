#ifndef ERRORS_H_
#define ERRORS_H_

// Errors
//
// Error and warning handling.
//
// Seto Balian, Feb 11, 2014

#include "types.h"

namespace SpinDecoherence
{

class Errors
{

public:

  static void quit();
  
  static void quit(const string & message);
  static void warning(const string & message);

};

} // namespace SpinDecoherence

#endif // ERRORS_H_
