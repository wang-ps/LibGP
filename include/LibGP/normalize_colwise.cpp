#include "normalize_colwise.h"

namespace LibGP
{
	template <typename Derived>
	LIBGP_INLINE void  normalize_colwise(Eigen::MatrixBase<Derived>& A)
	{
		int n = A.cols();
		#pragma omp parallel for
		for (int j = 0; j < n; j++)
		{
			Float d = A.col(j).norm();
			if (d < EPS) d = EPS;
			A.col(j) /= d;
		}
	}

#ifdef LIBPG_STATIC_LIBRARY
// Explicit template specialization
template<>
void LibGP::normalize_colwise<MatrixXf>(const Eigen::MatrixBase<MatrixXf>&);
#endif
}

