// See Errors.h for description.
// Seto Balian, Feb 21, 2014

#include "Errors.h"
#include <cstdlib>

namespace SpinDecoherence
{

void Errors::quit()
{
  std::exit(1);
  return;
}

void Errors::quit(const string & message)
{
  cout << "!!! SpinDecoherence fatal error!" << endl;
  cout << "!!! " << message << endl;
  quit();
  return;
}

void Errors::warning(const string & message)
{
  cout << "!!! SpinDecoherence warning!" << endl;
  cout << "!!! " << message << endl;
  return;
}

} // namespace SpinDecoherence
