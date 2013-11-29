// To test SpinDecoherence
//
// Seto Balian, November 29, 2013

#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <cmath>
#include <vector>
#include "MathPhysConstants.h"
#include "BoostEigen.h"
#include "Spin.h"
#include "ElectronSpin.h"
#include "NuclearSpin.h"
#include "SpinBasis.h"
#include "SpinVector.h"

#include <cstdlib>


//#include "ZeemanBasis.h"
//#include "SpinInteractionGraph.h"

std::complex<double> test_exp(const std::complex<double> & z) {

  return std::complex<double>( exp(z.real())*cos(z.imag()) ,
                               exp(z.real())*sin(z.imag()) );

}

int main () {


//SpinVector spin_vector;
//ElectronSpin electron;
//NuclearSpin nucleus;
//
//spin_vector.push_back(electron);
//spin_vector.push_back(nucleus);
//
//Spin some_spin = spin_vector[electron];
//
//std::cout << some_spin.get_gyromagnetic_ratio() << std::endl; 
//exit(1);
  
std::cout << "TESTING MathPhysConstants\n" << std::endl;

std::cout << "pi " << MathPhysConstants::pi() << std::endl;
std::cout << "h " << MathPhysConstants::plank() << std::endl;
std::cout << "hbar " << MathPhysConstants::reduced_plank() << std::endl;
std::cout << std::endl;

std::cout << "TESTING BoostEigen\n" << std::endl;

Eigen::Vector3d aVec, bVec;

aVec << 0.0, 3.3, -1.2;
bVec << 1.2, -0.2, 0.8;

std::cout << "a" << aVec << std::endl;
std::cout << "b" << bVec << std::endl;

std::cout << "Angle between a and b ";
std::cout << BoostEigen::cosAngleBetween(aVec,bVec) << std::endl;
std::cout << std::endl;

std::cout << "Eigen exp(a)" << aVec.array().exp() << std::endl;

Eigen::Vector3d testv = (aVec.array().exp()).matrix();

std::cout << "test " << testv << std::endl;

Eigen::Array3cd complexvector(std::complex<double>(1.0,-1.0),
                             std::complex<double>(-1.0,-1.0),
                             std::complex<double>(0.0,-3.0));

std::cout << "complexvector" << complexvector << std::endl;
std::cout << "Eigen exp" << complexvector.exp() << std::endl;

std::cout << std::endl;

std::cout << "test_exp" << std::endl;
std::cout << test_exp(std::complex<double>(1.0,-1.0)) << std::endl;
std::cout << test_exp(std::complex<double>(-1.0,-1.0)) << std::endl;
std::cout << test_exp(std::complex<double>(0.0,-3.0)) << std::endl;

std::cout << std::endl;

std::cout << "polar(exp(1),-1)" << std::endl;
std::cout << std::polar( exp(1.0) , -1.0 ) << std::endl;

std::cout << std::endl;

Eigen::ArrayXXd rand1;
rand1.setRandom(4,3);

Eigen::ArrayXXd rand2(4,3);
rand2.setRandom(4,3);

std::cout << "rand1" << std::endl;
std::cout << rand1 << std::endl;

std::cout << "rand2" << std::endl;
std::cout << rand2 << std::endl;

std::cout << "horizontal append" << std::endl;
BoostEigen::horizontalAppend(rand1,rand2);
std::cout << rand1 << std::endl;

std::cout << "vertical append" << std::endl;
BoostEigen::verticalAppend(rand1,rand2);
std::cout << rand1 << std::endl;

std::cout << std::endl;


//std::cout << "TESTING SingleSpinZeemanBasis + dependencies\n" << std::endl;
//
//NuclearSpin nucleus(4.5,10,Eigen::Vector3d::Zero());
//ElectronSpin electron;
//ElectronSpin electron2;
//
//electron.add_magnetic_quantum_number(-0.5);
//electron.add_magnetic_quantum_number(0.5);
////electron.add_magnetic_quantum_number(3.5);
//
//electron2.add_magnetic_quantum_number(1.5);
//electron2.add_magnetic_quantum_number(2.5);
////electron2.add_magnetic_quantum_number(-9.5);
////electron2.add_magnetic_quantum_number(-9.5);
//
//
//ZeemanBasis combined_basis = electron.get_zeeman_basis();
//
//combined_basis.append(electron2.get_zeeman_basis());
//
//nucleus.build_zeeman_basis();
//
//std::cout << nucleus.get_zeeman_basis().get_basis() << std::endl << std::endl;
//std::cout << electron.get_zeeman_basis().get_basis() << std::endl << std::endl;
//std::cout << combined_basis.get_basis() << std::endl << std::endl;
//
//SingleSpinZeemanBasis test_combine = nucleus.get_zeeman_basis();
//ZeemanBasis combined = electron.get_zeeman_basis();
//
//std::cout << "electron" << std::endl;
//
//std::cout << combined.get_basis() << std::endl;
//
//std::cout << "electron + nucleus" << std::endl;
//test_combine.combine(combined);
//std::cout << combined.get_basis() << std::endl;
//
//std::cout << "electron + nucleus + electron" << std::endl;
//test_combine = electron.get_zeeman_basis();
//test_combine.combine(combined);
//std::cout << combined.get_basis() << std::endl;


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
