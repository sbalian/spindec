// See StringOptions.h for description.
// Seto Balian, May 21, 2014

#include "SpinDec/StringOptions.h"

namespace SpinDec
{

StringOptions::StringOptions()
{
  options_ = "";
}

StringOptions::StringOptions(const string& options)
{
  options_ = options;
}

bool StringOptions::found_option(const char option) const
{
  for (UInt i = 0; i< options_.length() ; i++) {
    if (options_[i] == option) {
      return true;
    }
  }
  return false;
}

bool StringOptions::is_empty() const
{
  if (options_ == "") {
    return true;
  }
  return false;
}


} // namespace SpinDec

