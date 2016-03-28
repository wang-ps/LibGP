#pragma once
#include "libgp_inline.h"
#include <Eigen/Sparse>
#include <vector>

namespace LibGP
{
	LIBGP_INLINE void list_to_adj(
		Eigen::SparseMatrix<double>& A,
		const std::vector<std::vector<int>>& vec);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "list_to_adj.cpp"
#endif