#pragma once
#include "libgp_inline.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>

namespace LibGP
{
	LIBGP_INLINE void compute_adj_matrix(
		Eigen::SparseMatrix<double>& A,
		const Eigen::MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_adj_matrix.cpp"
#endif