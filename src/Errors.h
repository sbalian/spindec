#ifndef ERRORS_H_
#define ERRORS_H_

// Errors
//
// Error and warning handling.
//
// Seto Balian, Dec 3, 2013

#include <string>

class Errors
{

public:

  static void quit();
  
  static void quit(const std::string & message);
  static void warning(const std::string & message);

};

#endif // ERRORS_H_
