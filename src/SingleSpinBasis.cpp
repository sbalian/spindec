// See SingleSpinBasis.h for description.
// Seto Balian, Dec 4, 2013

#include "SingleSpinBasis.h"

void SingleSpinBasis::build(const Spin & spin)
{
  SpinBasis::build(SpinVector(spin));
}

SingleSpinBasis::SingleSpinBasis() : SpinBasis() {/**/}

SingleSpinBasis::SingleSpinBasis(const Spin & spin)
{
  build(spin);
}

SingleSpinBasis::SingleSpinBasis(const Eigen::ArrayXd & basis) :
  SpinBasis(basis)
{/**/} // TODO is this OK? ArrayXd vs ArrayXXd

unsigned int SingleSpinBasis::num_spins() const
{
  return 1;
}

double SingleSpinBasis::get_element(const unsigned int index) const
{
  return SpinBasis::get_element(index,0);
}

SingleSpinBasis::~SingleSpinBasis() {/**/}

