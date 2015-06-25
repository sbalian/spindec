#ifndef SPINPARAMETERS_H_
#define SPINPARAMETERS_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/**
 * \brief Contains basic parameters associated with a spin.
 * 
 * - Quantum number \f$S\f$.
 * - Gyromagnetic ratio \f$ \gamma \f$ [M rad s\f$^{-1}\f$ T\f$^{-1}\f$].
 * - Spin multiplicity \f$ 2 S + 1 \f$.
 * 
 * \f$ \gamma = \omega / B\f$ where \f$ \omega \f$ is the Larmor frequency
 * in M rad s\f$^{-1}\f$ and \f$ B \f$ is the magnetic field in Tesla (T).
 * 
 */
class SpinParameters
{
protected:

  // Data members
  double quantum_number_;
  double gyromagnetic_ratio_;
  UInt multiplicity_;

  // Protected methods
  UInt multiplicity(const double quantum_number) const;

public:

  // Constructors
  SpinParameters();
  SpinParameters(const double quantum_number,
                 const double gyromagnetic_ratio);

  // Access methods
  
  double get_quantum_number() const;
  double get_gyromagnetic_ratio() const;
  UInt get_multiplicity() const;
  
  /// Print with cout.
  friend std::ostream& operator<<(std::ostream& os,
      SpinParameters const & spin_parameters);

};

} // namespace SpinDec

#endif // SPINPARAMETERS_H_
