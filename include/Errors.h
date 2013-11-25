#ifndef ERRORS_H
#define ERRORS_H

// Errors
//
// Error and warning handling.
//
// Seto Balian 25/11/2013

#include <string>
#include "Named.h"

class Errors
{

public:

  static void quit();
  
  static void quit(const Named & named, const std::string & message);
  static void warning(const Named & named, const std::string & message);
  
  static void quit(const std::string & static_class_name,
                  const std::string & message);
  static void warning(const std::string & static_class_name,
                  const std::string & message);


};

#endif // ERRORS_H
