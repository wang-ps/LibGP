#pragma once
#include "libgp_global.h"

namespace LibGP {

template <typename DerivedV, typename DerivedF>
LIBGP_INLINE Float compute_avg_edge_length(
    const Eigen::MatrixBase<DerivedV>& V,
    const Eigen::MatrixBase<DerivedF>& F);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_avg_edge_length.cpp"
#endif