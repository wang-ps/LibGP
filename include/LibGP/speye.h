#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE void speye(SMatrixf& smat,
    const int n, const Float v = 1.0);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "speye.cpp"
#endif