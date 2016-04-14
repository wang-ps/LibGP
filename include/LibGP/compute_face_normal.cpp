#include "compute_face_normal.h"

namespace LibGP
{
	template <typename DerivedV, typename DerivedF>
	LIBGP_INLINE void compute_face_normal(
		MatrixXf& Nf, VectorXf& f_areas,
		const Eigen::MatrixBase<DerivedV>& V,
		const Eigen::MatrixBase<DerivedF>& F)
	{
		size_t nf = F.cols();
		Nf.resize(3, nf);
		f_areas.resize(nf);

		#pragma omp parallel for
		for (int i = 0; i < nf; i++)
		{
			Vector3f p01 = V.col(F(1, i)) - V.col(F(0, i));
			Vector3f p02 = V.col(F(2, i)) - V.col(F(0, i));
			Vector3f n = p01.cross(p02);

			Float d = n.norm();
			if (d < EPS) d = EPS;
			n /= d;

			f_areas[i] = d*0.5;
			Nf.col(i) = n;
		}
	}

	template <typename DerivedV, typename DerivedF>
	LIBGP_INLINE void compute_face_normal(
		MatrixXf& Nf,
		const Eigen::MatrixBase<DerivedV>& V,
		const Eigen::MatrixBase<DerivedF>& F)
	{
		VectorXf f_areas;
		compute_face_normal(Nf, f_areas, V, F);
	}
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