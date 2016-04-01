#include "compute_avg_edge_length.h"

template <typename DerivedV, typename DerivedF>
LIBGP_INLINE double LibGP::compute_avg_edge_length(
	const Eigen::MatrixBase<DerivedV>& V,
	const Eigen::MatrixBase<DerivedF>& F)
{
	double avg_len = 0;
#pragma omp parallel for reduction(+:avg_len)
	for (int j = 0; j < F.cols(); j++)
	{
		double d = 0;
		for (int i = 0; i < F.rows(); i++)
		{
			d += (V.col(F(i, j)) - V.col(F((i + 1) % F.rows(), j))).norm();
		}
		avg_len += d;
	}

	return avg_len / (double)(3*F.cols());
}

#ifdef LIBPG_STATIC_LIBRARY
// Explicit template specialization
template<> 
double LibGP::compute_avg_edge_length<Eigen::MatrixXd, Eigen::MatrixXi>(
	const Eigen::MatrixBase<Eigen::MatrixXd>&,
	const Eigen::MatrixBase<Eigen::MatrixXi>&);
#endif
