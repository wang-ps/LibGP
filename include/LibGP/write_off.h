#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE bool write_off(std::string filename,
    const MatrixXf& V, const MatrixXi& F);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "write_off.cpp"
#endif