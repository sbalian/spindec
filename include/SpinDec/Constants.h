#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/// Mathematical and physical constants.
class Constants
{
  
public:

  // Math
  
  /**
   * \brief Pi.
   * 
   * From Wikipedia 06/12/2012.
   * 
   */
  static const double kPi;  
  
  // Physics
  
  /**
   * \brief Reduced Planck constant (J s).
   * 
   * From CODATA 06/12/2012.
   * 
   */
  static const double kReducedPlanck;

  /**
   * \brief Plank constant (J s).
   * 
   * From CODATA 06/12/2012.
   * 
   */
  static const double kPlanck;

  /**
   * \brief Electronic gyromagnetic ratio (M rad s\f$^{-1}\f$ T\f$^{-1}\f$).
   * 
   * From CODATA 22/10/2013.
   * 
   */
  static const double kElectronGyromagneticRatio;

};

} // namespace SpinDec

#endif // CONSTANTS_H_


