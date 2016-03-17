#pragma once
#include "libgp_inline.h"
#include "read_obj.h"
#include "read_off.h"

namespace LibGP
{
	LIBGP_INLINE bool read_mesh( std::string filename, 
		Eigen::MatrixXd& V, Eigen::MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "read_mesh.cpp"
#endif