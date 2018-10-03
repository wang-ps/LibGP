#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE void compute_face_grad(
    Matrix3f& grad, const Float* pv0, const Float* pv1, const Float* pv2);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_face_grad.cpp"
#endif