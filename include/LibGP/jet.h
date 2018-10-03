#pragma once
#include "libgp_global.h"

namespace LibGP {

LIBGP_INLINE void jet(MatrixXf &C, const VectorXf &X);

LIBGP_INLINE void jet(MatrixXf &C, const std::vector<Float> &X);

LIBGP_INLINE void jet(MatrixXf &C, const VectorXf &X, Float min, Float max);

LIBGP_INLINE void jet(Float &r, Float &g, Float &b, Float x);

// Eigen::MatrixXd colormap(3, 4);
// colormap << 0.4824, 0.7608, 0, 0.6510,
//	 0.1961, 0.6471, 0.5333, 0.8588,
//	 0.5804, 0.8118, 0.2157, 0.6275;
// Eigen::MatrixXd colormap(3, 8);
// colormap << 0.4627, 0.6000, 0.7608, 0.9059, 0.8510, 0.6510, 0.3529, 0.1059,
//	 0.1647, 0.4392, 0.6471, 0.8314, 0.9412, 0.8588, 0.6824, 0.4706,
//	 0.5137, 0.6706, 0.8118, 0.9098, 0.8275, 0.6275, 0.3804, 0.2157;

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "jet.cpp"
#endif

