#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE void compute_vtx_adj(
    SMatrixf& A, const MatrixXi& F);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_vtx_adj.cpp"
#endif