#pragma once
#include "libgp_inline.h"
#include <Eigen/Dense>
#include <vector>

namespace LibGP
{
	LIBGP_INLINE void reconstruct_mesh_LS(
		Eigen::MatrixXd& V1,
		const Eigen::MatrixXd& V,
		const Eigen::MatrixXi& F,
		const Eigen::MatrixXd& N1,
		int it_num = 20);

	LIBGP_INLINE void reconstruct_mesh_LS(
		Eigen::MatrixXd& V1,
		const Eigen::MatrixXd& V,
		const Eigen::MatrixXi& F,
		const Eigen::MatrixXd& N1,
		const std::vector<std::vector<int>>& vf_ring,
		int it_num = 20);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "reconstruct_mesh_LS.cpp"
#endif