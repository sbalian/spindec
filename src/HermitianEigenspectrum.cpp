// See HermitianEigenspectrum.h for description.
// Seto Balian, Dec 5, 2013

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

void HermitianEigenspectrum::diagonalize_zheev(
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
    for (q=0;q<n;q++) {
      a[r].real = matrix(q,p).real();
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

  eigenvalues_ = Eigen::VectorXd(n);
  eigenvectors_ = Eigen::MatrixXcd(n,n);

  for (p=0;p<n;p++) {
    eigenvalues_(p) = w[p];
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
  eigenvalues_  = eigensolver.eigenvalues();
  return;
}

HermitianEigenspectrum::HermitianEigenspectrum()
{/**/}

HermitianEigenspectrum::HermitianEigenspectrum(
    const Eigen::MatrixXcd & matrix)
{
  diagonalize(matrix);
}

HermitianEigenspectrum::HermitianEigenspectrum(const Eigen::MatrixXcd & matrix,
    const std::string & diagonalizer_type)
{
  diagonalize(matrix,diagonalizer_type);
}

void HermitianEigenspectrum::diagonalize(const Eigen::MatrixXcd & matrix)
{
  diagonalize_eigen(matrix);
}

void HermitianEigenspectrum::diagonalize(const Eigen::MatrixXcd & matrix,
    const std::string & diagonalizer_type)
{
  if (diagonalizer_type == "eigen") {
    diagonalize_eigen(matrix);
    return;
  }
  
  if (diagonalizer_type == "zheev") {
    diagonalize_zheev(matrix);
    return;
  }
  
  // else
  std::string message = "Diagonalizer \"";
  message += diagonalizer_type;
  message += "\" not supported.";
  Errors::quit(message);
  return;
  
}

Eigen::VectorXd HermitianEigenspectrum::get_eigenvalues() const
{
  return eigenvalues_;
}

Eigen::MatrixXcd HermitianEigenspectrum::get_eigenvectors() const
{
  return eigenvectors_;
}

double HermitianEigenspectrum::get_eigenvalue(const unsigned int index) const
{
  return eigenvalues_(index);
}

Eigen::VectorXcd HermitianEigenspectrum::get_eigenvector(
    const unsigned int index) const
{
  return eigenvectors_.col(index);
}

Eigen::MatrixXcd HermitianEigenspectrum::expSpectralDecomposition(
                                    const std::complex<double> & a) const
{
  return BoostEigen::expHermitianSpectralDecomposition(eigenvectors_,
      eigenvalues_,a);
}
