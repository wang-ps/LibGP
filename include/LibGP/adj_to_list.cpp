#include "adj_to_list.h"

LIBGP_INLINE void LibGP::adj_to_list(
	std::vector<std::vector<int>>& vec, 
	const Eigen::SparseMatrix<double>& A)
{
	vec.resize(A.cols());
	for (int k = 0; k < A.outerSize(); ++k)
	{
		for (Eigen::SparseMatrix<double>::InnerIterator it(A, k); it; ++it)
		{
			if (it.row() != it.col()) vec[k].push_back(it.row());
		}
	}
}