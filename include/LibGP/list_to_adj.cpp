#include "list_to_adj.h"

LIBGP_INLINE void LibGP::list_to_adj(
	Eigen::SparseMatrix<double>& A,
	const std::vector<std::vector<int>>& vec)
{
	typedef Eigen::Triplet<double> Tripletd;
	typedef Eigen::SparseMatrix<double> SMatrixd;

	int jmax = 0;
	std::vector<Tripletd> coeff;
	for (int i = 0; i < vec.size(); i++)
	{
		for (const int& j : vec[i])
		{
			if (j > jmax) jmax = j;
			coeff.push_back(Tripletd(i, j, 1));
		}		
	}

	A.resize(vec.size(), jmax + 1);
	A.reserve(coeff.size());
	A.setFromTriplets(coeff.begin(), coeff.end());
}