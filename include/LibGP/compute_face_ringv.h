#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE void compute_face_ringv(
    vecveci& vec, const MatrixXi& F);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_face_ringv.cpp"
#endif