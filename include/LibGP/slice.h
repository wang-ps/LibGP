#pragma once
#include "libgp_global.h"

namespace LibGP {

// slice : B = A(flag)
// slice_into : A = B(flag)

LIBGP_INLINE void slice(MatrixXf& B, VectorXb& flag, const MatrixXf& A);
LIBGP_INLINE void slice_into(MatrixXf& A, VectorXb& flag, const MatrixXf& B);

LIBGP_INLINE void slice(MatrixXf& B, std::vector<int>& idx, const MatrixXf& A);
LIBGP_INLINE void slice_into(MatrixXf& A, std::vector<int>& idx, const MatrixXf& B);

LIBGP_INLINE void slice_into(VectorXi& A, VectorXb& flag, const int b);
LIBGP_INLINE void slice_into(VectorXi& A, std::vector<int>& idx, const int b);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "slice.cpp"
#endif
