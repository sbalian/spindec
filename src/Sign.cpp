// See Sign.h for description.
// Seto Balian, Mar 24, 2014

#include "SpinDec/Sign.h"

namespace SpinDec
{

const Sign Sign::Plus(1);
const Sign Sign::Minus(-1);

int Sign::as_int() const
{
  return value_;
}

bool Sign::isPlus() const
{
  if (value_ == 1) {
    return true;
  }
  return false;
}

bool Sign::isMinus() const
{
  return !isPlus();
}

Sign::Sign(const int value) :
    value_(value)
{
}

bool Sign::operator==(const Sign& rhs) const
{
  if (rhs.as_int() == as_int()) {
    return true;
  } else {
    return false;
  }
}

std::ostream& operator<<(std::ostream& os, Sign const & sign)
{
  
  if (sign.isPlus()) {
    os << '+';
  } else {
    os << '-';
  }
  return os;
}


} // namespace SpinDec

//// TEST
//#include <iostream>
//using namespace SpinDec;
//int main()
//{
//  std::cout << (Sign::Plus == Sign::Plus) << std::endl;
//  return 0;
//}
//// g++ ../src/Sign.cpp -I../src/include/ -o SIGN
