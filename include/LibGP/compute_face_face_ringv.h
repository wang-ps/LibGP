#pragma once
#include "libgp_inline.h"
#include <Eigen/Dense>
#include <vector>

namespace LibGP
{
	LIBGP_INLINE void compute_face_face_ringv(
		std::vector<std::vector<int>>& vec,
		const Eigen::MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_face_face_ringv.cpp"
#endif