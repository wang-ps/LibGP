#pragma once
#include "libgp_global.h"

namespace LibGP
{
	template <typename DerivedV, typename DerivedF>
		LIBGP_INLINE bool write_off(std::string filename,
		const Eigen::MatrixBase<DerivedV>& V,
		const Eigen::MatrixBase<DerivedF>& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "write_off.cpp"
#endif