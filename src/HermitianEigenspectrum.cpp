// See HermitianEigenspectrum.h for description.
// Seto Balian, Apr 7, 2014

#include "SpinDec/HermitianEigenspectrum.h"
#include "SpinDec/BoostEigen.h"
#include "SpinDec/Errors.h"

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

namespace SpinDec
{

void HermitianEigenspectrum::diagonalize_lapack(
    const ComplexMatrix & matrix)
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
      a[r].real = CDouble(matrix(q,p)).real();
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
  eigenvectors_ = ComplexMatrix(n,n);

  for (p=0;p<n;p++) {
    eigenvalues_(p) = CDouble(w[p],0.0);
  }

  r = 0;
  for (p=0;p<n;p++) {
    for (q=0;q<n;q++) {
      eigenvectors_(q,p) = CDouble(a[r].real,a[r].imag);
      r = r + 1;
    }
  }
  
  /* Free workspace */
  free( (void*)work );
  return;
  
}

void HermitianEigenspectrum::diagonalize_eigen(
    const ComplexMatrix & matrix)
{
  Eigen::SelfAdjointEigenSolver<ComplexMatrix> eigensolver(matrix.rows());
  eigensolver.compute(matrix);

  eigenvectors_ = eigensolver.eigenvectors();
  eigenvalues_  = (eigensolver.eigenvalues()).cast< CDouble > ();
  return;
  
}

HermitianEigenspectrum::HermitianEigenspectrum() :
    Eigenspectrum()
{/**/}

HermitianEigenspectrum::HermitianEigenspectrum(
    const ComplexMatrix & matrix) : Eigenspectrum()
{
  diagonalize(matrix);
}

HermitianEigenspectrum::HermitianEigenspectrum(const ComplexMatrix & matrix,
    const string & diagonalizer) : 
        Eigenspectrum(diagonalizer)
{
  diagonalize(matrix);
}

void HermitianEigenspectrum::diagonalize(const ComplexMatrix & matrix)
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

ComplexMatrix HermitianEigenspectrum::spectralDecomposition() const
{
  // since eigenvectors orthonormal, V-1 = V^+
  return BoostEigen::unitarySpectralDecomposition(eigenvectors_, eigenvalues_);
}

} // namespace SpinDec
