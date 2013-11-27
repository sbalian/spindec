// See Errors.h for description.
// Seto Balian, November 27, 2013

#include "Errors.h"
#include <cstdlib>
#include <iostream>

void Errors::quit()
{
  exit(1);
  return;
}

void Errors::quit(const std::string & message)
{
  std::cout << "### FATAL ERROR!" << std::endl;
  std::cout << "    " << message << std::endl;
  quit();
  return;
}

void Errors::warning(const std::string & message)
{
  std::cout << "### WARNING!" << std::endl;
  std::cout << "    " << message << std::endl;
  return;
}
