#ifndef STRINGOPTIONS_H_
#define STRINGOPTIONS_H_

// SpinDec::StringOptions
//
// String flags composed of A-Z, a-z, each character representing a flag.
//
// Seto Balian, Nov 6, 2014

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class StringOptions
{
private:
  string options_;
  
public:
  StringOptions();
  StringOptions(const string & options);
  
  bool found_option(const char option) const;
  bool is_empty() const;
  
};

} // namespace SpinDec

#endif // STRINGOPTIONS_H_
