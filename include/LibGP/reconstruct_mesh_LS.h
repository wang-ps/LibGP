#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE void reconstruct_mesh_LS(
    MatrixXf& V1,
    const MatrixXf& V,
    const MatrixXi& F,
    const MatrixXf& N1,
    int it_num = 20);

LIBGP_INLINE void reconstruct_mesh_LS(
    MatrixXf& V1,
    const MatrixXf& V,
    const MatrixXi& F,
    const MatrixXf& N1,
    const vecveci& vf_ring,
    int it_num = 30);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "reconstruct_mesh_LS.cpp"
#endif