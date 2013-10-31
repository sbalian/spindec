#ifndef ERRORS_H
#define ERRORS_H

// Errors
//
// Error and warning handling.
//
// Seto Balian 31/10/2013

#include <string>

class Errors
{

public:

  static void quit();
  static void quit(const std::string & message);
  static void warning(const std::string & message);

};

#endif // ERRORS_H

