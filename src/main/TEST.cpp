// To test SpinDecoherence
//
// Seto Balian, November 26, 2013

#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <cmath>

//#include "ZeemanBasis.h"
//#include "SpinInteractionGraph.h"

#include "NuclearSpin.h"
#include "ElectronSpin.h"

int main () {

std::cout << "TESTING SingleSpinZeemanBasis + dependencies\n" << std::endl;

NuclearSpin nucleus(4.5,10,Eigen::Vector3d::Zero());
ElectronSpin electron;
ElectronSpin electron2;

electron.add_magnetic_quantum_number(-0.5);
electron.add_magnetic_quantum_number(0.5);
//electron.add_magnetic_quantum_number(3.5);

electron2.add_magnetic_quantum_number(1.5);
electron2.add_magnetic_quantum_number(2.5);
//electron2.add_magnetic_quantum_number(-9.5);
//electron2.add_magnetic_quantum_number(-9.5);


ZeemanBasis combined_basis = electron.get_zeeman_basis();

combined_basis.append(electron2.get_zeeman_basis());

nucleus.build_zeeman_basis();

std::cout << nucleus.get_zeeman_basis().get_basis() << std::endl << std::endl;
std::cout << electron.get_zeeman_basis().get_basis() << std::endl << std::endl;
std::cout << combined_basis.get_basis() << std::endl << std::endl;

SingleSpinZeemanBasis test_combine = nucleus.get_zeeman_basis();
ZeemanBasis combined = electron.get_zeeman_basis();

std::cout << "electron" << std::endl;

std::cout << combined.get_basis() << std::endl;

std::cout << "electron + nucleus" << std::endl;
test_combine.combine(combined);
std::cout << combined.get_basis() << std::endl;

std::cout << "electron + nucleus + electron" << std::endl;
test_combine = electron.get_zeeman_basis();
test_combine.combine(combined);
std::cout << combined.get_basis() << std::endl;


//SpinInteractionGraph graph;
//
//SpinInteractionNode electron_node(electron,Eigen::VectorXcd::Zero(0),0);
//SpinInteractionNode nucleus_node(nucleus,Eigen::VectorXcd::Zero(0),1);
//
//graph.add_node(electron_node);
//graph.add_node(nucleus_node);
//electron_node.set_label(2);
//graph.add_node(electron_node);
//
//graph.add_vertex(0,1,"",50.0);
//
//ZeemanBasis test_basis;
//test_basis.build(graph);
//
//std::cout << "basis" << std::endl;
//std::cout << test_basis.get_basis() << std::endl;
//
//Eigen::ArrayXXd to_keep(3,2);
//
//to_keep << 0.5 , 4.5,
//          -0.5, 2.5,
//           0.5, -1.5;
//
//std::vector<unsigned int> indices;
//
//indices.push_back(0);
//indices.push_back(1);
//
//test_basis.truncate(indices,to_keep);
//
//std::cout << "truncated" << std::endl;
//std::cout << test_basis.get_basis() << std::endl;


return 0;

}
