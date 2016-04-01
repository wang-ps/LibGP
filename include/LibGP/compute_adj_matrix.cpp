#include "compute_adj_matrix.h"

LIBGP_INLINE void LibGP::compute_adj_matrix(Eigen::SparseMatrix<double>& A, const Eigen::MatrixXi& F)
{
	typedef Eigen::Triplet<double> Tripletd;
	typedef Eigen::SparseMatrix<double> SMatrixd;

	std::vector<Tripletd> coeff;
	coeff.reserve(3 * F.cols());
	for (int i = 0; i < F.cols(); i++)
	{
		coeff.push_back(Tripletd(F(0, i), F(1, i), 1.0));
		coeff.push_back(Tripletd(F(1, i), F(2, i), 1.0));
		coeff.push_back(Tripletd(F(2, i), F(0, i), 1.0));
	}

	int nv = F.maxCoeff() + 1;
	SMatrixd T(nv, nv);
	T.setFromTriplets(coeff.begin(), coeff.end());

	A = SMatrixd(T.transpose()) + T;	
	double* p = A.valuePtr();
	for (int i = 0; i < A.nonZeros(); i++)
	{
		*(p + i) = 1.0;
	}
}


