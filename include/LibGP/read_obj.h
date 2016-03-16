#pragma once
#include "libgp_inline.h"
#include <Eigen/Dense>

namespace LibGP
{
	LIBGP_INLINE bool read_obj( std::string filename, 
		Eigen::MatrixXd& V, Eigen::MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "read_obj.cpp"
#endif