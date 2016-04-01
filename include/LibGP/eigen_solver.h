#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void eigen_solver(
		Eigen::VectorXd& eig_values,
		Eigen::MatrixXd& eig_vectors,
		const Eigen::MatrixXd& A,
		const bool ascending = true);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "eigen_solver.cpp"
#endif
