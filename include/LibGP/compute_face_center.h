#pragma once
#include "libgp_global.h"

namespace LibGP {

template <typename DerivedFC, typename DerivedV, typename DerivedF>
LIBGP_INLINE void compute_face_center(
    Eigen::MatrixBase<DerivedFC>& FC,
    const Eigen::MatrixBase<DerivedV>& V,
    const Eigen::MatrixBase<DerivedF>& F);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_face_center.cpp"
#endif