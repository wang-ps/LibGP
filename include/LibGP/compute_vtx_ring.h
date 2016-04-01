#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void compute_vtx_ring(
		std::vector<std::vector<int>>& vec,
		const Eigen::MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_vtx_ring.cpp"
#endif