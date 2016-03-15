#include "compute_face_center.h"

template <typename DerivedFC, typename DerivedV, typename DerivedF>
LIBGP_INLINE void LibGP::compute_face_center(
	Eigen::MatrixBase<DerivedFC>& FC,
	const Eigen::MatrixBase<DerivedV>& V, 
	const Eigen::MatrixBase<DerivedF>& F)
{
	FC = Eigen::MatrixBase<DerivedV>::Zero(F.rows(), F.cols());
	for (size_t i = 0; i < F.cols(); i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			FC.col(i) += V.col(F(j, i));
		}
	}

	FC /= 3.0;	
}

#ifdef LIBPG_STATIC_LIBRARY
// Explicit template specialization
template<>
void LibGP::compute_face_center<Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXi>(
		  Eigen::MatrixBase<Eigen::MatrixXd>&
	const Eigen::MatrixBase<Eigen::MatrixXd>&,
	const Eigen::MatrixBase<Eigen::MatrixXi>&);
#endif