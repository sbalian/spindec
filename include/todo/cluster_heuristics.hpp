#ifndef CLUSTERHEURISTICS_H
#define CLUSTERHEURISTICS_H

// Cluster heuristics
//
// Created  09/10/2012
// Modified 05/11/2012
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "threevector.hpp"

using namespace std;

class cluster_heuristics
{

public:

static bool heuristics_2cluster ( const  threevector & r_1,  const threevector & r_2, const double cutoff_sq );
static bool heuristics_2cluster ( const  threevector & r, const double cutoff_sq );
static bool heuristics_3cluster ( const threevector & r_1, const threevector & r_2, const  threevector & r_3, const double cutoff_sq );

};

#endif // CLUSTERHEURISTICS_H

