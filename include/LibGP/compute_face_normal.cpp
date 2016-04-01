#include "compute_face_normal.h"

template <typename DerivedV, typename DerivedF>
LIBGP_INLINE void LibGP::compute_face_normal(
	Eigen::MatrixXd& Nf, Eigen::VectorXd& F_areas,
	const Eigen::MatrixBase<DerivedV>& V, 
	const Eigen::MatrixBase<DerivedF>& F)
{
	size_t nf = F.cols();
	Nf.resize(3, nf);
	F_areas.resize(nf);

#pragma omp parallel for
	for (int i = 0; i < nf; i++)
	{
		Eigen::Vector3d p01 = V.col(F(1, i)) - V.col(F(0, i));
		Eigen::Vector3d p02 = V.col(F(2, i)) - V.col(F(0, i));
		Eigen::Vector3d n = p01.cross(p02);

		double d = n.norm();
		if (d < EPS) d = EPS;
		n /= d;

		F_areas[i] = d*0.5;
		Nf.col(i) = n;
	}
}

template <typename DerivedV, typename DerivedF>
LIBGP_INLINE void LibGP::compute_face_normal(
	Eigen::MatrixXd& Nf, 
	const Eigen::MatrixBase<DerivedV>& V,
	const Eigen::MatrixBase<DerivedF>& F)
{
	Eigen::VectorXd F_areas;
	LibGP::compute_face_normal(Nf, F_areas, V, F);
}

#ifdef LIBPG_STATIC_LIBRARY
// Explicit template specialization
template<>
void LibGP::compute_face_normal<Eigen::MatrixXd, Eigen::MatrixXi>(
	Eigen::MatrixXd&,
	const Eigen::MatrixBase<Eigen::MatrixXd>&,
	const Eigen::MatrixBase<Eigen::MatrixXi>&);
void LibGP::compute_face_normal<Eigen::MatrixXd, Eigen::MatrixXi>(
	Eigen::MatrixXd&, Eigen::VectorXd& F_areas,
	const Eigen::MatrixBase<Eigen::MatrixXd>&,
	const Eigen::MatrixBase<Eigen::MatrixXi>&);
#endif