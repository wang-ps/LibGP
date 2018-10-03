#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE void compute_mesh_grad(
    SMatrixf& G, const MatrixXf& V, const MatrixXi& F);

LIBGP_INLINE void compute_mesh_grad(
    SMatrixf& G, std::vector<Matrix3f>& Gv,
    const MatrixXf& V, const MatrixXi& F);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_mesh_grad.cpp"
#endif