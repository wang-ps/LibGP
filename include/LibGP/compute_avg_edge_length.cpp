#include "compute_avg_edge_length.h"

template <typename DerivedV, typename DerivedF>
LIBGP_INLINE double LibGP::compute_avg_edge_length(
	const Eigen::MatrixBase<DerivedV>& V,
	const Eigen::MatrixBase<DerivedF>& F)
{
	double avg_len = 0;
	size_t n = 0;
	for (size_t j = 0; j < F.cols(); j++)
	{
		for (size_t i = 0; i < F.rows(); i++)
		{
			avg_len += (V.col(F(i, j)) - V.col(F((i + 1) % F.rows(), j))).norm();
			n++;
		}
	}

	return avg_len / (double)n;
}

#ifdef LIBPG_STATIC_LIBRARY
// Explicit template specialization
template<> 
double LibGP::compute_avg_edge_length<Eigen::MatrixXd, Eigen::MatrixXi>(
	const Eigen::MatrixBase<Eigen::MatrixXd>&,
	const Eigen::MatrixBase<Eigen::MatrixXi>&);
#endif
