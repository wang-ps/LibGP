#pragma once
#include "libgp_global.h"

namespace LibGP
{
	// slice : B = A(flag)
	// slice_into : A = B(flag)

	LIBGP_INLINE void slice(Eigen::MatrixXd& B, LibGP::VectorXb& flag, const Eigen::MatrixXd& A);
	LIBGP_INLINE void slice_into(Eigen::MatrixXd& A, LibGP::VectorXb& flag, const Eigen::MatrixXd& B);

	LIBGP_INLINE void slice(Eigen::MatrixXd& B, std::vector<int>& idx, const Eigen::MatrixXd& A);
	LIBGP_INLINE void slice_into(Eigen::MatrixXd& A, std::vector<int>& idx, const Eigen::MatrixXd& B);

	LIBGP_INLINE void slice_into(Eigen::VectorXi& A, LibGP::VectorXb& flag, const int b);
	LIBGP_INLINE void slice_into(Eigen::VectorXi& A, std::vector<int>& idx, const int b);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "slice.cpp"
#endif
