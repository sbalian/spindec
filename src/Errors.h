#ifndef ERRORS_H_
#define ERRORS_H_

// Errors
//
// Error and warning handling.
//
// Seto Balian, Feb 6, 2014

#include <string>

namespace SpinDecoherence
{

class Errors
{

public:

  static void quit();
  
  static void quit(const std::string & message);
  static void warning(const std::string & message);

};

} // namespace SpinDecoherence

#endif // ERRORS_H_
