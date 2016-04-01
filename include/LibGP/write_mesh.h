#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE bool write_mesh(std::string filename,
		Eigen::MatrixXd& V, Eigen::MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "write_mesh.cpp"
#endif