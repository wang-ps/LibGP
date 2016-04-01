#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE bool write_obj(std::string filename,
		Eigen::MatrixXd& V, Eigen::MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "write_obj.cpp"
#endif