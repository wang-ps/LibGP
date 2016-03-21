#pragma once
#include "libgp_inline.h"
#include <Eigen/Sparse>
#include <vector>

namespace LibGP
{
	LIBGP_INLINE void adj_to_list(
		std::vector<std::vector<int>>& vec,
		const Eigen::SparseMatrix<double>& A);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "adj_to_list.cpp"
#endif