#ifndef ERRORS_H
#define ERRORS_H

// Errors
//
// TODO Describe
//
// Seto Balian 04/10/2013

#include <string>

class Errors
{

public:

  static void quit();
  static void quit(const std::string & message);
  static void warning(const std::string & message);

};

#endif // ERRORS_H

