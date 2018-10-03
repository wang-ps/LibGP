#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE bool read_mesh(std::string filename,
    MatrixXf& V, MatrixXi& F);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "read_mesh.cpp"
#endif