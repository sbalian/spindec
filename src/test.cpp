// For testing SpinDecoherence
// Seto Balian, Dec 11, 2013

#include <iostream>
#include <complex>
#include <cmath>
#include <Eigen/Dense>

#include "BoostEigen.h"
#include "MathPhysConstants.h"
#include "Spin.h"
#include "NuclearSpin.h"
#include "ElectronSpin.h"
#include "SpinBasis.h"
#include "SingleSpinBasis.h"
#include "SpinVector.h"

//std::complex<double> test_exp(const std::complex<double> & z)
//{
//  return std::complex<double>( exp(z.real())*cos(z.imag()) ,
//                               exp(z.real())*sin(z.imag()) );
//}

int main() {
  
ElectronSpin electron;

std::cout << electron << std::endl;

//  std::cout << "TESTING BoostEigen\n" << std::endl;
//
//  Eigen::Vector3d a_3vec, b_3vec;
//  a_3vec << 0.0, 3.3, -1.2;
//  b_3vec << 1.2, -0.2, 0.8;
//
//  std::cout << "Vector a_3vec\n" << a_3vec << std::endl;
//  std::cout << "Vector b_3vec\n" << b_3vec << std::endl;
//
//  std::cout << "Cosine of angle between a_3vec and b_3vec is ";
//  std::cout << BoostEigen::cosAngleBetween(a_3vec,b_3vec) << std::endl;
//  std::cout << std::endl;
//
//  std::cout << "Maximum of absolute coefficients of a_3vec is ";
//  std::cout << BoostEigen::maxAbsCoeff(a_3vec) << std::endl;
//
//  Eigen::ArrayXXd A_array(2,3);
//  A_array << 0.5, 3.3, 6.0,
//             1.1, 4.4, 8.9;
//  std::cout << "Array A_array\n" << A_array << std::endl;
//
//  Eigen::VectorXcd c_3cvec(3);
//  c_3cvec << std::complex<double>(2.0,4.4),
//             std::complex<double>(1.0,3.4),
//             std::complex<double>(2.0,-4.4);
//  std::cout << "Complex vector c_3cvec\n" << c_3cvec << std::endl;
//  std::cout << "Exponential of c_3cvec is\n";
//  std::cout << BoostEigen::exp(c_3cvec) << std::endl;
//  std::cout << "Exponential of a_3vec is\n";
//  std::cout << BoostEigen::exp(a_3vec) << std::endl;
//
//  Eigen::ArrayXXd rand1;
//  rand1.setRandom(4,3);
//
//  Eigen::ArrayXd rand2;
//  rand2.setRandom(4);
//
//  std::cout << "rand1\n";
//  std::cout << rand1 << std::endl;
//  std::cout << "rand2\n";
//  std::cout << rand2 << std::endl;
//
//  Eigen::ArrayXXd joined(4,4);
//  joined << rand1, rand2;
//
//  std::cout << "joined\n";
//  std::cout << joined << std::endl;
//
//  Eigen::MatrixXcd matrix1 = Eigen::MatrixXcd::Random(2,2);
//  Eigen::MatrixXcd matrix2 = Eigen::MatrixXcd::Random(2,2);
//
//  std::cout << "matrix1\n";
//  std::cout << matrix1 << std::endl;
//
//  std::cout << "matrix2\n";
//  std::cout << matrix2 << std::endl;
//
//  std::cout << "matrix1 X(tensor) matrix2\n";
//  std::cout << BoostEigen::tensorProduct(matrix1,matrix2) << std::endl;
//
//  Eigen::VectorXcd vector1 = Eigen::VectorXcd::Random(2);
//  Eigen::VectorXcd vector2 = Eigen::VectorXcd::Random(2);
//
//  std::cout << "vector1\n";
//  std::cout << vector1 << std::endl;
//
//  std::cout << "vector2\n";
//  std::cout << vector2 << std::endl;
//
//  std::cout << "vector1 X(tensor) vector2\n";
//  std::cout << BoostEigen::tensorProduct(vector1,vector2) << std::endl;
//
//  std::cout << "TESTING MathPhysConstants\n" << std::endl;
//
//  std::cout << "pi " << MathPhysConstants::pi() << std::endl;
//  std::cout << "h " << MathPhysConstants::plank() << std::endl;
//  std::cout << "hbar " << MathPhysConstants::reduced_plank() << std::endl;
//  std::cout << std::endl;
//
//  std::cout << "TESTING exp\n" << std::endl;
//
//  Eigen::Vector3d aVec, bVec;
//
//  aVec << 0.0, 3.3, -1.2;
//  bVec << 1.2, -0.2, 0.8;
//
//  std::cout << "a" << aVec << std::endl;
//  std::cout << "b" << bVec << std::endl;
//
//  std::cout << "Eigen exp(a)" << aVec.array().exp() << std::endl;
//
//  Eigen::Vector3d testv = (aVec.array().exp()).matrix();
//
//  std::cout << "test " << testv << std::endl;
//
//  Eigen::Array3cd complexvector(std::complex<double>(1.0,-1.0),
//                               std::complex<double>(-1.0,-1.0),
//                               std::complex<double>(0.0,-3.0));
//
//  std::cout << "complexvector" << complexvector << std::endl;
//  std::cout << "Eigen exp" << complexvector.exp() << std::endl;
//
//  std::cout << std::endl;
//
//  std::cout << "test_exp" << std::endl;
//  std::cout << test_exp(std::complex<double>(1.0,-1.0)) << std::endl;
//  std::cout << test_exp(std::complex<double>(-1.0,-1.0)) << std::endl;
//  std::cout << test_exp(std::complex<double>(0.0,-3.0)) << std::endl;
//
//  std::cout << std::endl;
//
//  std::cout << "polar(exp(1),-1)" << std::endl;
//  std::cout << std::polar( exp(1.0) , -1.0 ) << std::endl;
//
//  std::cout << std::endl;
//  
//  std::cout << "TESTING spins\n" << std::endl;
//  
//  SpinVector spin_vector;
//  ElectronSpin electron;
//  NuclearSpin nucleus(4.5,0.0);
//
//  spin_vector.push_back(electron);
//  spin_vector.push_back(nucleus);
//
//  Spin some_spin = spin_vector.get_spin(0);
//
//  std::cout << some_spin.get_gyromagnetic_ratio() << std::endl;
  
//  Eigen::ArrayXXd basis1;
//  Eigen::ArrayXd basis2;
//  
//  std::cout << basis1.rows() << "\t" << basis1.cols() << std::endl;
//  std::cout << basis2.rows() << "\t" << basis2.cols() << std::endl;
//
//  basis1 = basis2;
//  
//  std::cout << basis1.rows() << "\t" << basis1.cols() << std::endl;

  
//  std::cout << "TESTING bases\n" << std::endl;
//    
//  SingleSpinBasis electron_basis(electron);
//  SingleSpinBasis nucleus_basis(nucleus);
//  
//  std::cout << "Electron basis\n" << electron_basis.get_basis() << std::endl;
//  std::cout << "Nucleus basis\n" << nucleus_basis.get_basis() << std::endl;
//  
//  SpinBasis combined;
//  combined = nucleus_basis^((electron_basis)^(electron_basis));
//  
//  std::cout << "Combined basis\n" << combined.get_basis() << std::endl;
//
//  
//  SpinBasis combined2 = electron_basis^electron_basis;
//  SpinBasis combined3 = combined2^combined2;
//  std::cout << "test\n" << combined3.get_basis() << std::endl;
//  
  
      
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
//
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


