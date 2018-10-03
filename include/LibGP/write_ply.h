#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE extern void write_ply(
    const std::string &filename,
    const MatrixXf &V,
    const MatrixXi &F,
    const MatrixXf &UV = MatrixXf(),
    const std::vector<std::string> comments = std::vector<std::string>(),
    const MatrixXu8 &C = MatrixXu8());

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "write_ply.cpp"
#endif