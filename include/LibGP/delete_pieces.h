#pragma once
#include "libgp_global.h"

namespace LibGP {

// min_num: -1, keep only the max piece; otherwise keep the pieces whose
// face number is larger than min_num
void delete_pieces(MatrixXf& V, MatrixXi& F, int min_num = -1);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "delete_pieces.cpp"
#endif