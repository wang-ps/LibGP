#ifndef SAMPLE_POINTS_H_
#define SAMPLE_POINTS_H_

#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE void sample_points(
    MatrixXf& pts, MatrixXf& normals,
    const MatrixXf& V, const MatrixXi& F, Float area_unit = 0.5f);

} // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "sample_points.cpp"
#endif

#endif
