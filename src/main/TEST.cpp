// To test SpinDecoherence
//
// Seto Balian 20/11/2013

#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <cmath>

#include "ZeemanBasis.h"
#include "SpinInteractionGraph.h"

#include "NuclearSpin.h"
#include "ElectronSpin.h"

int main () {

std::cout << "TESTING ZeemanBasis + dependencies\n" << std::endl;

NuclearSpin nucleus(4.5,10,Eigen::Vector3d::Zero());
ElectronSpin electron;

SpinInteractionGraph graph;

SpinInteractionNode electron_node(electron,Eigen::VectorXcd::Zero(0),0);
SpinInteractionNode nucleus_node(nucleus,Eigen::VectorXcd::Zero(0),1);

graph.add_node(electron_node);
graph.add_node(nucleus_node);
electron_node.set_label(2);
graph.add_node(electron_node);

graph.add_vertex(0,1,"",50.0);

ZeemanBasis test_basis;
test_basis.build(graph);

std::cout << "basis" << std::endl;
std::cout << test_basis.get_basis() << std::endl;

Eigen::ArrayXXd to_keep(3,2);

to_keep << 0.5 , 4.5,
          -0.5, 2.5,
           0.5, -1.5;

std::vector<unsigned int> indices;

indices.push_back(0);
indices.push_back(1);

test_basis.truncate(indices,to_keep);

std::cout << "truncated" << std::endl;
std::cout << test_basis.get_basis() << std::endl;


return 0;

}