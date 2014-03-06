// See Errors.h for description.
// Seto Balian, Mar 6, 2014

#include "SpinDec/Errors.h"
#include <cstdlib>

namespace SpinDec
{

void Errors::quit()
{
  std::exit(1);
  return;
}

void Errors::quit(const string & message)
{
  cout << "!!! SpinDec fatal error!" << endl;
  cout << "!!! " << message << endl;
  quit();
  return;
}

void Errors::warning(const string & message)
{
  cout << "!!! SpinDec warning!" << endl;
  cout << "!!! " << message << endl;
  return;
}

} // namespace SpinDec
