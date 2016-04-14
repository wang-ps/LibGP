#pragma once
#include "libgp_global.h"

namespace LibGP
{
	template <typename DerivedV, typename DerivedF>
	LIBGP_INLINE void compute_normal(
		MatrixXf& Nv, MatrixXf& Nf, VectorXf& F_area,
		const Eigen::MatrixBase<DerivedV>& V,
		const Eigen::MatrixBase<DerivedF>& F);

	template <typename DerivedV, typename DerivedF>
	LIBGP_INLINE void compute_normal(
		MatrixXf& Nv, MatrixXf& Nf,
		const Eigen::MatrixBase<DerivedV>& V,
		const Eigen::MatrixBase<DerivedF>& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_normal.cpp"
#endif