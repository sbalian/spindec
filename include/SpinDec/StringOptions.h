#ifndef STRINGOPTIONS_H_
#define STRINGOPTIONS_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/// String flags composed of A-Z, a-z, each character representing a flag.
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
