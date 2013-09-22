// (Quantum) operator on a Hilbert space in the (complex) matrix representation.
// Acts on complex vectors (class "statevector").
// NOTE: must be Hermitian
//
// Created  05/11/2011
// Modified 19/09/2012, 20/09/2012, 22/09/2012, 26/09/2012, 27/09/2012,
// 28/09/2012, 30/09/2012, 01/10/2012, 02/10/2012, 04/10/2012, 06/10/2012
// 14/11/2012, 03/12/2012
// Modified 11/12/2012 - exponentiate method speed improvement
// Modified 16/05/2013, 17/05/2013
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "statevector.hpp"
#include "qoperator.hpp"

using namespace std;
using namespace Eigen;

qoperator::qoperator()
{
//
}

qoperator::qoperator(const int dim)
{
  MatrixXcd zero_matrix(dim,dim);
  zero_matrix.setZero();

  VectorXd zero_vector(dim);
  zero_vector.setZero();

  set_matrix_rep(zero_matrix);
  set_eigenvalues(zero_vector);
  set_eigenvectors(zero_matrix);
}

qoperator::qoperator(const MatrixXcd & matrix_rep_in) {
  
  int dim = matrix_rep_in.rows();

  MatrixXcd zero_matrix(dim,dim);
  zero_matrix.setZero();

  VectorXd zero_vector(dim);
  zero_vector.setZero();

  set_matrix_rep(matrix_rep_in);
  set_eigenvalues(zero_vector);
  set_eigenvectors(zero_matrix);
}

qoperator::qoperator(const MatrixXcd & matrix_rep_in, const VectorXd & eigenvalues_in, const MatrixXcd & eigenvectors_in) {
  set_matrix_rep(matrix_rep_in);
  set_eigenvalues(eigenvalues_in);
  set_eigenvectors(eigenvectors_in);
}

qoperator::qoperator(const statevector & state, const statevector & dualstate) {

  set_matrix_rep(state, dualstate);
  int dim = matrix_rep.rows();

  MatrixXcd zero_matrix(dim,dim);
  zero_matrix.setZero();

  VectorXd zero_vector(dim);
  zero_vector.setZero();

  set_eigenvalues(zero_vector);
  set_eigenvectors(zero_matrix);
}

MatrixXcd qoperator::get_matrix_rep() const {
  return matrix_rep;
}

void qoperator::set_matrix_rep(const MatrixXcd & matrix_rep_in) {
  matrix_rep = matrix_rep_in;
  return;
}

void qoperator::set_matrix_rep(const statevector & state, const statevector & dualstate ) {
  set_matrix_rep (   state.get_col_vec()*(dualstate.get_col_vec().adjoint())    );
  return;
}

// Get the eigenvalues
VectorXd qoperator::get_eigenvalues() const
{
  return eigenvalues;
}

// Get the eigenvectors
MatrixXcd qoperator::get_eigenvectors() const
{
  return eigenvectors;
}

void qoperator::set_eigenvalues(const VectorXd & eigenvalues_in) {
  eigenvalues = eigenvalues_in;
  return;
}

void qoperator::set_eigenvectors(const MatrixXcd & eigenvectors_in) {
  eigenvectors = eigenvectors_in;
  return;
}

cmplxd qoperator::get_element(const int i, const int j) const {
  return matrix_rep(i,j);
}

void qoperator::set_element(const int i, const int j, const cmplxd & element_in) {
  matrix_rep(i,j) = element_in;
  return;
}

int qoperator::dimension() const {
  return matrix_rep.cols();
}

qoperator qoperator::operator+(const qoperator & toadd) const {
  MatrixXcd zero_matrix(dimension(),dimension());
  zero_matrix.setZero();
  VectorXd zero_vector(dimension());
  zero_vector.setZero();
  return qoperator( matrix_rep + toadd.matrix_rep, zero_vector, zero_matrix);
}

qoperator qoperator::operator-(const qoperator & tosubtract) const {
  MatrixXcd zero_matrix(dimension(),dimension());
  zero_matrix.setZero();
  VectorXd zero_vector(dimension());
  zero_vector.setZero();
  return qoperator( matrix_rep - tosubtract.matrix_rep, zero_vector, zero_matrix );
}

qoperator qoperator::operator*(const cmplxd & complexnumber) const {
  MatrixXcd zero_matrix(dimension(),dimension());
  zero_matrix.setZero();
  VectorXd zero_vector(dimension());
  zero_vector.setZero();
  return qoperator ( matrix_rep*complexnumber, zero_vector, zero_matrix );
}

statevector qoperator::operator*(const statevector & operand) const {
  return statevector ( matrix_rep*operand.get_col_vec());
}

qoperator qoperator::operator^(const qoperator & operator_in) const {
  int dim_in = operator_in.dimension();
  int dim    = dimension();

  MatrixXcd tensorproduct(dim*dim_in,dim*dim_in);
  tensorproduct.setZero();

  int i,j;
  for (i=0;i<dim;i++) {
    for (j=0;j<dim;j++) {

      tensorproduct.block(i*dim_in,j*dim_in,dim_in,dim_in) = matrix_rep(i,j)*(operator_in.matrix_rep);

    }
  }

  MatrixXcd zero_matrix(dimension(),dimension());
  zero_matrix.setZero();
  VectorXd zero_vector(dimension());
  zero_vector.setZero();
  
  return qoperator(tensorproduct, zero_vector, zero_matrix);
  
}

void qoperator::diagonalise(const string & option) {
  if (option == "eigen") {
    diagonalise_eigen();
  } else {
      diagonalise_zheev();
    }
  return;
}

//void qoperator::diagonalise_zheev() {
//  diagonalise_eigen();
//  return;
//}

// Diagonalise the Hamiltonian using Lapack zheev
void qoperator::diagonalise_zheev()
{

  set_eigenvalues_zeros();
  set_eigenvectors_zeros();

  // Dimension
	int n = dimension();

	int lda = n;			// dimension	// NOTE: INTEL
	int info, lwork;    // NOTE: INTEL
	MKL_Complex16 wkopt;			// NOTE: INTEL
	MKL_Complex16* work;			// NOTE: INTEL
	// rwork dimension should be at least max(1,3*n-2) // NOTE: INTEL

	// Martin Uhrin: Cannot use a variable to allocate a static array as
	// the size is not known at compile time!  You have to use pointers
	// and the 'new' operator if you want to do this, as below.
	 double w[n], rwork[3*n-2]; // NOTE: INTEL
//	double * w		= (double *)malloc(n * sizeof(double));		
//	double * rwork	= (double *)malloc((3 * n - 2) * sizeof(double));	

	MKL_Complex16 a[lda*n]; // NOTE: INTEL

	int p,q,r;

	r = 0;
	
	for (p=0;p<n;p++) {
		for (q=0;q<n;q++) {
			a[r].real = matrix_rep(q,p).real();
			a[r].imag = 0.0;
			r = r + 1;
		}
	}

	// NOTE: CHANGING LWORK AND WORK DIMENSION TO THE ONES USED IN F90 PROGRAM
	//			 AND OTHER VALUES MADE NO DIFFERENCE TO THE FIRST EIGENVALUE ...

	/* Query and allocate the optimal workspace */ // NOTE: INTEL
	lwork = -1; // NOTE: INTEL
	zheev_( "Vectors", "Lower", &n, a, &lda, w, &wkopt, &lwork, rwork, &info ); // NOTE: INTEL
	lwork = (int)wkopt.real; // NOTE: INTEL
	//lwork = 321;
	work = (MKL_Complex16*)malloc( lwork*sizeof(MKL_Complex16) ); // NOTE: INTEL
	//work = (MKL_Complex16*)malloc( 56232 );
	/* Solve eigenproblem */ // NOTE: INTEL

	zheev_( "Vectors", "Lower", &n, a, &lda, w, work, &lwork, rwork, &info ); // NOTE: INTEL

	// Check for convergence // NOTE: INTEL
	if ( info != 0 ) { // NOTE: INTEL (changed > to != )
		printf( "The algorithm failed to compute eigenvalues.\n" ); // NOTE: INTEL
		exit( 1 ); // NOTE: INTEL
	}

	for (p=0;p<n;p++) {
		eigenvalues(p) = w[p];
	}


	r = 0;
	for (p=0;p<n;p++) {
		for (q=0;q<n;q++) {
			eigenvectors(q,p) = cmplxd(a[r].real,a[r].imag);
			r = r + 1;
		}
	}
	/* Free workspace */ // NOTE: INTEL
	free( (void*)work );
  return;

}

void qoperator::diagonalise_eigen() {

  set_eigenvalues_zeros();
  set_eigenvectors_zeros();

  // Diagonalise
	SelfAdjointEigenSolver<MatrixXcd> eigensolver(dimension());
	eigensolver.compute(matrix_rep);

	eigenvectors = eigensolver.eigenvectors();
	eigenvalues  = eigensolver.eigenvalues();

	return;
}

void qoperator::diagonalise() {
  diagonalise_zheev();
  return;
}

void qoperator::set_zeros() {
  matrix_rep.setZero();
  return;
}

void qoperator::set_eigenvalues_zeros() {
  eigenvalues.setZero();
  return;
}

void qoperator::set_eigenvectors_zeros() {
  eigenvectors.setZero();
  return;
}


// NOTE: Units?
void qoperator::print(const string & option) const
{ 
  int i;
  
  for (i=0; i< int (option.length() ); i++) {
  
    if (option[i] == 'w') {
			
	      int evalsp = 15;
        VectorXd evals = get_eigenvalues();
        int dim = dimension();
        //NOTE: CHECK UNITS
        int i;
        cout << "'qoperator' " << get_name() << " eigenvalues in increasing order:" << endl;
        cout << "Label          Eigenvalue      " << endl;
        cout << "-----     -------------------- " << endl;
        for (i=0;i<dim;i++) {
					cout << setiosflags(ios::left);
          cout << setw(10)       << setprecision(3) << i+1;
					cout << setw(evalsp+2) << setprecision(evalsp) << evals(i) << endl;     
        }
        cout << endl;


    }
		
    if (option[i] == 'f') {
			
				int evalsp = 15;
        VectorXd evals = get_eigenvalues()/(2.0*PI);
        int dim = dimension();
        //NOTE: CHECK UNITS
        int i;
        cout << "'qoperator' " << get_name() << " eigenvalues in increasing order:" << endl;
        cout << "Label          Eigenvalue   *  " << endl;
        cout << "-----     ---------------------" << endl;
        for (i=0;i<dim;i++) {
					cout << setiosflags(ios::left);
          cout << setw(10)       << setprecision(3) << i+1;
					cout << setw(evalsp+2) << setprecision(evalsp) << evals(i) << endl;     
        }
        cout << endl;
        cout << "* These have been divided by 2pi." << endl;
        cout << endl;


    }
    
    if (option[i] == 'E') {
        cout << "'qoperator' " << get_name() << " eigenvectors:" << endl;
        cout << get_eigenvectors() << endl;
        cout << endl;
    }
    
    if (option[i] == 'M') {
        cout << "'qoperator' " << get_name() << " matrix representation:" << endl;
      cout << matrix_rep << "\n" << endl;
    }

    if (option[i] == 'R') {
        cout << "'qoperator' " << get_name() << " real matrix representation (imaginary part ignored):" << endl;
      MatrixXd real_matrix(dimension(),dimension());
      int i, j;
      for (i=0;i<dimension();i++) {
        for (j=0;j<dimension();j++) {
          real_matrix(i,j) = matrix_rep(i,j).real();
        }
      }
      cout << real_matrix << "\n" << endl;
    }
  
  }
  return;
}

// This method calculates the following given real alpha:
// e^(-i M alpha) = Sum_over_n_up_to_dim { |psi_n> e^(-i E_n alpha) <psi_n| },
// where M is the matrix, |psi_n> are its eigenvectors, E_n
// the eigenvalues and dim is the dimension of the Hilbert space.

qoperator qoperator::exponentiate(const double alpha) const  {


  int dim = dimension();

  MatrixXcd diageigmatrix(dim,dim);
  diageigmatrix.setZero();

  int i;
  for (i=0;i<dim;i++) {
    diageigmatrix(i,i) = polar(1.0,-(get_eigenvalues()(i))*alpha);
  }

  MatrixXcd matrix_out(dim,dim);
  matrix_out.setZero();

  matrix_out = get_eigenvectors()*(diageigmatrix*(get_eigenvectors().adjoint()));

//  long double real_ld = 0.0;
//  long double imag_ld = 0.0;
//  long double alpha_ld = 0.0;
//  long double eval_ld = 0.0;

//  double real_d = 0.0;
//  double imag_d = 0.0;

////  int i;
////  for (i=0;i<dim;i++) {
//////    eval_ld = (long double)get_eigenvalues()(i);
//////    alpha_ld = (long double)alpha;
//////    real_ld =  cos( eval_ld*alpha_ld );
//////    imag_ld = -sin( eval_ld*alpha_ld );
//////    real_d = real_ld;
//////    imag_d = imag_ld;

////    //matrix_out = matrix_out + ((get_eigenvectors().col(i))*complex <double> ((double)real_ld,(double)imag_ld))*(get_eigenvectors().col(i).adjoint());

////    matrix_out += ((get_eigenvectors().col(i))*polar(1.0,-(get_eigenvalues()(i))*alpha))*(get_eigenvectors().col(i).adjoint());

////  }

  MatrixXcd zero_matrix(dimension(),dimension());
  zero_matrix.setZero();
  VectorXd zero_vector(dimension());
  zero_vector.setZero();

  return qoperator(matrix_out, zero_vector, zero_matrix);

}

qoperator qoperator::partial_trace(const int degrees_of_freedom) const {
  MatrixXcd matrix_out(dimension()/degrees_of_freedom,dimension()/degrees_of_freedom);
  int i = 0;
  int j = 0;
  while (i<=dimension()-degrees_of_freedom) {
    j = 0;
    while (j<=dimension()-degrees_of_freedom) {
      matrix_out(i/degrees_of_freedom,j/degrees_of_freedom) = (get_matrix_rep().block(i,j,degrees_of_freedom,degrees_of_freedom)).trace();
      j = j + degrees_of_freedom;
    }
    i = i + degrees_of_freedom;
  }

  MatrixXcd zero_matrix(matrix_out.rows(),matrix_out.rows());
  zero_matrix.setZero();
  VectorXd zero_vector(matrix_out.rows());
  zero_vector.setZero();  

  return qoperator(matrix_out,zero_vector,zero_matrix);
  
}

// NOTE: Add checks and explain this method
VectorXcd qoperator::get_eigenvector(ArrayXi levels, const int level) const {
  VectorXcd evec;
  std::sort(levels.data(), levels.data()+levels.size());
  int i;
  for (i=0;i<levels.rows();i++) {
    if (level == levels(i)) {
//      cout << "asked for level " << level << " and got col " << i << endl;
      evec = eigenvectors.col(i);
      break;
    }
  }
  return evec;
}

qoperator qoperator::Identity(const int dim) {
  MatrixXcd zero_matrix(dim,dim);
  zero_matrix.setZero();
  VectorXd zero_vector(dim);
  zero_vector.setZero();
  return qoperator(MatrixXcd::Identity(dim,dim),zero_vector,zero_matrix);
}


