#ifndef SIGN_H_
#define SIGN_H_

// Seto Balian, Jun 24, 2015

#include <iostream>

namespace SpinDec
{

/// \f$\pm\f$.
class Sign
{
public:
  static const Sign Plus;
  static const Sign Minus;
  
  int as_int() const;
  
  bool isPlus() const;
  bool isMinus() const;
  
  bool operator==(const Sign& rhs) const;
  
  /// Print with cout.
  friend std::ostream& operator<<(std::ostream& os, Sign const & sign);
  
private:
  int value_;
  Sign(const int value);
  
};

} // namespace SpinDec

#endif // SIGN_H_
