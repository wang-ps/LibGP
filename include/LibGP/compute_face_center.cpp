#include "compute_face_center.h"

template <typename DerivedFC, typename DerivedV, typename DerivedF>
LIBGP_INLINE void LibGP::compute_face_center(
	Eigen::MatrixBase<DerivedFC>& Fc,
	const Eigen::MatrixBase<DerivedV>& V, 
	const Eigen::MatrixBase<DerivedF>& F)
{
	Fc = Eigen::MatrixBase<DerivedV>::Zero(F.rows(), F.cols());
	#pragma omp parallel for
	for (int i = 0; i < F.cols(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Fc.col(i) += V.col(F(j, i));
		}
		Fc.col(i) /= 3.0;
	}
}

#ifdef LIBPG_STATIC_LIBRARY
// Explicit template specialization
template<>
void LibGP::compute_face_center<Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXi>(
		  Eigen::MatrixBase<Eigen::MatrixXd>&,
	const Eigen::MatrixBase<Eigen::MatrixXd>&,
	const Eigen::MatrixBase<Eigen::MatrixXi>&);
#endif