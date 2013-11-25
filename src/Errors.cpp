// See Errors.h for description.
// Seto Balian 25/11/2013

#include "Errors.h"
#include <cstdlib>
#include <iostream>

void Errors::quit()
{
  exit(1);
  return;
}

void Errors::quit(const Named & named, const std::string & message)
{
  std::cout << "FATAL ERROR!" << std::endl;
  std::cout << "Class  : " << named.get_class_name() << std::endl;
  std::cout << "Intance: " << named.get_object_name() << std::endl;
  std::cout << "Details: " << message << std::endl;
  quit();
  return;
}

void Errors::warning(const Named & named, const std::string & message)
{
  std::cout << "WARINING!" << std::endl;
  std::cout << "Class  : " << named.get_class_name() << std::endl;
  std::cout << "Intance: " << named.get_object_name() << std::endl;
  std::cout << "Details: " << message << std::endl;
  return;
}

void Errors::quit(const std::string & static_class_name,
                  const std::string & message) {
  std::cout << "FATAL ERROR!" << std::endl;
  std::cout << "Static class: " << static_class_name << std::endl;
  std::cout << "Details     : " << message << std::endl;
  quit();
  return;
}

void Errors::warning(const std::string & static_class_name,
                  const std::string & message) {
  std::cout << "WARNING!" << std::endl;
  std::cout << "Static class: " << static_class_name << std::endl;
  std::cout << "Details     : " << message << std::endl;
  return;
}
