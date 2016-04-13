#include "compute_adj_matrix.h"

namespace LibGP
{
	LIBGP_INLINE void compute_adj_matrix(SMatrixf& A, const MatrixXi& F)
	{
		std::vector<Tripletf> coeff;
		coeff.reserve(3 * F.cols());
		for (int i = 0; i < F.cols(); i++)
		{
			coeff.push_back(Tripletf(F(0, i), F(1, i), 1.0));
			coeff.push_back(Tripletf(F(1, i), F(2, i), 1.0));
			coeff.push_back(Tripletf(F(2, i), F(0, i), 1.0));
		}

		int nv = F.maxCoeff() + 1;
		SMatrixf T(nv, nv);
		T.setFromTriplets(coeff.begin(), coeff.end());

		A = SMatrixf(T.transpose()) + T;
		Float* p = A.valuePtr();
		for (int i = 0; i < A.nonZeros(); i++)
		{
			*(p + i) = 1.0;
		}
	}
}



