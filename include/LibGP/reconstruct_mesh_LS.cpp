#include "reconstruct_mesh_LS.h"
#include "compute_vtx_face_ring.h"
#include "compute_face_center.h"


LIBGP_INLINE void LibGP::reconstruct_mesh_LS(
	Eigen::MatrixXd& V1, const Eigen::MatrixXd& V,
	const Eigen::MatrixXi& F, const Eigen::MatrixXd& N1, int it_num /* = 20 */)
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
	const std::vector<std::vector<int>>& vf_ring, int it_num /* = 20 */)
{
	// iteration
	Eigen::MatrixXd Fc, V1 = V;
	for (int it = 0; it < it_num; it++)
	{
		// compute face center
		LibGP::compute_face_center(Fc, V, F);

		// update vertex
		#pragma omp parallel for
		for (int i = 0; i < vf_ring.size(); i++)
		{
			Eigen::Vector3d vt(0, 0, 0);
			for (int& fi : vf_ring[i])
			{
				vt += N.col(fi) * (N.col(fi).dot(Fc.col(fi) - V.col(i)));
			}
			V.col(i) += vt / (double)vf_ring[i].size();
		}
	}
}