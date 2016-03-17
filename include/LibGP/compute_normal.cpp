#include "compute_normal.h"
#include "compute_face_normal.h"
#include "normalize_colwise.h"
#include <omp.h>

template <typename DerivedV, typename DerivedF>
LIBGP_INLINE void LibGP::compute_normal(
	Eigen::MatrixXd& Nv, Eigen::MatrixXd& Nf, Eigen::VectorXd& F_area,
	const Eigen::MatrixBase<DerivedV>& V,
	const Eigen::MatrixBase<DerivedF>& F)
{
	LibGP::compute_face_normal(Nf, F_area, V, F);
	Eigen::MatrixXd Nfw = Nf * F_area.asDiagonal();
	
	Nv = Eigen::MatrixXd::Zero(3, V.cols());
	for (int i = 0; i < F.cols(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Nv.col(F(j, i)) += Nfw.col(i);
		}
	}

	LibGP::normalize_colwise(Nv);	
}

template <typename DerivedV, typename DerivedF>
LIBGP_INLINE void compute_normal(
	Eigen::MatrixXd& Nv, Eigen::MatrixXd& Nf,
	const Eigen::MatrixBase<DerivedV>& V,
	const Eigen::MatrixBase<DerivedF>& F)
{
	Eigen::VectorXd F_area;
	LibGP::compute_normal(Nv, Nf, F_area, V, F);
}


#ifdef LIBPG_STATIC_LIBRARY
//Explicit template specialization
template<>
void LibGP::compute_normal<Eigen::MatrixXd, Eigen::MatrixXi>(
	Eigen::MatrixXd&, Eigen::MatrixXd& , Eigen::VectorXd&,
	const Eigen::MatrixBase<Eigen::MatrixXd>&,
	const Eigen::MatrixBase<Eigen::MatrixXi>&);
void LibGP::compute_normal<Eigen::MatrixXd, Eigen::MatrixXi>(
	Eigen::MatrixXd&,  Eigen::MatrixXd&,
	const Eigen::MatrixBase<Eigen::MatrixXd>&,
	const Eigen::MatrixBase<Eigen::MatrixXi>&);
#endif