#ifndef ERRORS_H_
#define ERRORS_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/// Error and warning handling.
class Errors
{

public:

  static void quit();
  static void quit(const string & message);
  static void warning(const string & message);

};

} // namespace SpinDec

#endif // ERRORS_H_
