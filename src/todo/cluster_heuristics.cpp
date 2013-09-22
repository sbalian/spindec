// Cluster heuristics
//
// Created  09/10/2012
// Modified 05/11/2012
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "cluster_heuristics.hpp"
#include "threevector.hpp"
                          
using namespace std;

bool cluster_heuristics::heuristics_2cluster ( const threevector & r_1, const  threevector &  r_2, const double cutoff_sq ) {

  if ( (r_2 - r_1).modSquared() <= cutoff_sq ) {
    return 1;
  } else {
      return 0;
    }

}

bool cluster_heuristics::heuristics_2cluster ( const threevector & r, const double cutoff_sq ) {

  if ( r.modSquared() <= cutoff_sq ) {
    return 1;
  } else {
      return 0;
    }

}

bool cluster_heuristics::heuristics_3cluster (  const threevector & r_1, const  threevector &  r_2, const threevector & r_3, const double cutoff_sq ) {

  if (
      ( ( (r_1 - r_2).modSquared() <= cutoff_sq )
    && ( (r_2 - r_3).modSquared() <= cutoff_sq ) )  ||
      ( ( (r_1 - r_3).modSquared() <= cutoff_sq )
    && ( (r_2 - r_3).modSquared() <= cutoff_sq ) )  ||
      ( ( (r_1 - r_2).modSquared() <= cutoff_sq )
    && ( (r_1 - r_3).modSquared() <= cutoff_sq ) )
    ) {return 1;} else {return 0;}

}


