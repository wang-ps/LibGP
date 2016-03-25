#include "reconstruct_mesh_LS.h"
#include "compute_vtx_face_ring.h"
#include "compute_face_center.h"


LIBGP_INLINE void LibGP::reconstruct_mesh_LS(
	Eigen::MatrixXd& V1, const Eigen::MatrixXd& V,
	const Eigen::MatrixXi& F, const Eigen::MatrixXd& N1, int it_num /* = 30 */)
{
	// compute vertex_face_ring
	std::vector<std::vector<int>> vf_ring;
	LibGP::compute_vtx_face_ring(vf_ring, F);

	// update vertex
	LibGP::reconstruct_mesh_LS(V1, V, F, N1, vf_ring, it_num);
}

LIBGP_INLINE void LibGP::reconstruct_mesh_LS(
	Eigen::MatrixXd& V1, const Eigen::MatrixXd& V,
	const Eigen::MatrixXi& F, const Eigen::MatrixXd& N1,
	const std::vector<std::vector<int>>& vf_ring, int it_num /* = 30 */)
{
	// init
	V1 = V;

	// iteration
	for (int it = 0; it < it_num; it++)
	{
		// compute face center
		Eigen::MatrixXd Fc;
		LibGP::compute_face_center(Fc, V1, F);

		// update vertex
		#pragma omp parallel for
		for (int i = 0; i < vf_ring.size(); i++)
		{
			Eigen::Vector3d vt(0, 0, 0);
			for (const int& fi : vf_ring[i])
			{
				vt += N1.col(fi) * (N1.col(fi).dot(Fc.col(fi) - V1.col(i)));
			}
			V1.col(i) += vt / (double)vf_ring[i].size();
		}
	}
}