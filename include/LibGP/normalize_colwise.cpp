#include "normalize_colwise.h"

template <typename Derived>
LIBGP_INLINE void  LibGP::normalize_colwise(Eigen::MatrixBase<Derived>& A)
{
	int n = A.cols();
#pragma omp parallel for
	for (int j = 0; j < n; j++)
	{
		double d = A.col(j).norm();
		if (d < EPS) d = ESP;
		A.col(j) /= d;
	}
}

#ifdef LIBPG_STATIC_LIBRARY
// Explicit template specialization
template<>
void LibGP::normalize_colwise<Eigen::MatrixXd>(const Eigen::MatrixBase<Eigen::MatrixXd>&);
#endif