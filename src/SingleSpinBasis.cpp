// See SingleSpinBasis.h for description.
// Seto Balian, Dec 5, 2013

#include "SingleSpinBasis.h"

Eigen::ArrayXXd SingleSpinBasis::build(const Spin & spin) const
{
  return SpinBasis::build(SpinVector(spin));
}

SingleSpinBasis::SingleSpinBasis() : SpinBasis() {/**/}

SingleSpinBasis::SingleSpinBasis(const Spin & spin)
{
  basis_ = build(spin);
}

SingleSpinBasis::SingleSpinBasis(const Eigen::ArrayXd & basis) :
  SpinBasis(basis)
{/**/} // TODO make sure this is OK: ArrayXd vs ArrayXXd

unsigned int SingleSpinBasis::num_spins() const
{
  return 1;
}

double SingleSpinBasis::get_element(const unsigned int index) const
{
  return SpinBasis::get_element(index,0);
}

SingleSpinBasis::~SingleSpinBasis() {/**/}

