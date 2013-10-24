// See Errors.h for description.
// Seto Balian 22/10/2013

#include "Errors.h"
#include <string>
#include <cstdlib>
#include <iostream>

void Errors::quit()
{
  exit(1);
  return;
}

void Errors::quit(const std::string & message)
{
  std::cout << "FATAL ERROR! ";
  std::cout << message;
  std::cout << std::endl;
  quit();
  return;
}

void Errors::warning(const std::string & message)
{
  std::cout << "WARNING! ";
  std::cout << message;
  std::cout << std::endl;
  return;
}

