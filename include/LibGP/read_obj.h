#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE bool read_obj(std::string filename,
    MatrixXf& V, MatrixXi& F);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "read_obj.cpp"
#endif