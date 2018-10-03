#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE void eigen_solver(
    VectorXf& eig_values,
    MatrixXf& eig_vectors,
    const MatrixXf& A,
    const bool ascending = true);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "eigen_solver.cpp"
#endif
