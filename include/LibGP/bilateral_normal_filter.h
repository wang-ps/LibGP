#pragma once
#include "libgp_global.h"

namespace LibGP{
	LIBGP_INLINE void bilateral_normal_filter(
		MatrixXf& V1, const MatrixXf& V, const MatrixXi& F,
		Float sigma_r = 0.35, Float sigma_s = 1.0, int it_n = 10, int it_v = 20);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "bilateral_normal_filter.cpp"
#endif