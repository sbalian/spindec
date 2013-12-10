// See HermitianEigenspectrum.h for description.
// Seto Balian, Dec 10, 2013

#include "HermitianEigenspectrum.h"
#include "BoostEigen.h"
#include "Errors.h"

// For Lapack zheev diagonalizer (Intel example TODO link)
// ---------------------------------------------
// Complex datatype
struct _MKL_Complex16 { double real, imag; };
typedef struct _MKL_Complex16 MKL_Complex16;
// zheev prototype (added "C" for C++)
extern "C" void zheev_(const char* jobz,const char* uplo, int* n,
    MKL_Complex16* a, int* lda, double* w, MKL_Complex16* work, int* lwork,
    double* rwork, int* info );
// ---------------------------------------------

void HermitianEigenspectrum::diagonalize_lapack(
    const Eigen::MatrixXcd & matrix)
{
  // Code adapted from Intel example TODO link

  // PREPARE
  
  int n = matrix.rows();  // dimension
  
  int lda = n;      // dimension
  int info, lwork;
  MKL_Complex16 wkopt;
  MKL_Complex16* work;
  // rwork dimension should be at least max(1,3*n-2)

  double w[n], rwork[3*n-2];
  MKL_Complex16 a[lda*n];
  int p,q,r;

  // put matrix into a C array
  r = 0;
  for (p=0;p<n;p++) {
    for (q=0;q<n;q++) { // TODO std complex set to MKL complex ... is this OK?
      a[r].real = std::complex<double>(matrix(q,p)).real();
      a[r].imag = 0.0;
      r = r + 1;
    }
  }

  // Query and allocate the optimal workspace
  lwork = -1;
  zheev_( "Vectors", "Lower", &n, a, &lda, w, &wkopt, &lwork, rwork, &info );
  lwork = (int)wkopt.real;
  //lwork = 321;
  work = (MKL_Complex16*)malloc( lwork*sizeof(MKL_Complex16) );
  
  // DIAGONALIZE

  zheev_( "Vectors", "Lower", &n, a, &lda, w, work, &lwork, rwork, &info );

  // Check for convergence
  if ( info != 0 ) { // changed > in Intel example to !=
    Errors::quit("zheev: The algorithm failed to compute eigenvalues.");
  }

  eigenvalues_ = Eigen::VectorXcd(n);
  eigenvectors_ = Eigen::MatrixXcd(n,n);

  for (p=0;p<n;p++) {
    eigenvalues_(p) = std::complex<double>(w[p],0.0);
  }

  r = 0;
  for (p=0;p<n;p++) {
    for (q=0;q<n;q++) {
      eigenvectors_(q,p) = std::complex<double>(a[r].real,a[r].imag);
      r = r + 1;
    }
  }
  
  /* Free workspace */
  free( (void*)work );
  return;
  
}

void HermitianEigenspectrum::diagonalize_eigen(
    const Eigen::MatrixXcd & matrix)
{
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXcd> eigensolver(matrix.rows());
  eigensolver.compute(matrix);

  eigenvectors_ = eigensolver.eigenvectors();
  eigenvalues_  = (eigensolver.eigenvalues()).cast< std::complex<double> > ();
  return;
  
}

HermitianEigenspectrum::HermitianEigenspectrum() :
    Eigenspectrum()
{/**/}

HermitianEigenspectrum::HermitianEigenspectrum(
    const Eigen::MatrixXcd & matrix) : Eigenspectrum()
{
  diagonalize(matrix);
}

HermitianEigenspectrum::HermitianEigenspectrum(const Eigen::MatrixXcd & matrix,
    const std::string & diagonalizer) : 
        Eigenspectrum(diagonalizer)
{
  diagonalize(matrix);
}

void HermitianEigenspectrum::diagonalize(const Eigen::MatrixXcd & matrix)
{
  if (diagonalizer_ == "Eigen") {
    diagonalize_eigen(matrix);
    return;
  }
  
  if (diagonalizer_ == "Lapack") {
    diagonalize_lapack(matrix);
    return;
  }
  
  // else
  quit_if_diagonalizer_not_supported();
  return;
  
}

Eigen::MatrixXcd HermitianEigenspectrum::spectralDecomposition() const
{
  // since eigenvectors orthonormal, V-1 = V^+
  return BoostEigen::unitarySpectralDecomposition(eigenvectors_, eigenvalues_);
}
