#pragma once

#if defined(WIN32)
#define _CRT_SECURE_NO_DEPRECATE
#define NOMINMAX
//#pragma warning(disable: 4244 4018 4100 4610 4510 4127 4512 4146 4267 4503 4800 4706)
#pragma warning(disable: 4244 4267 4800 4099)
#endif

/* inline */
#ifndef LIBPG_STATIC_LIBRARY
#  define LIBGP_INLINE inline
#else
#  define LIBGP_INLINE
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>
#include <omp.h>
#include <cstdint>
#include <string>
#include <Eigen/Dense>
#include <Eigen/Sparse>


using std::cout;
using std::cerr;
using std::endl;

namespace LibGP {

#define  SINGLE_PRECISION

/* Application precision -- can be set to single or Float precision */
#if defined(SINGLE_PRECISION)
typedef float Float;
#else
typedef double Float;
#endif

const Float EPS = 1.0e-20;

/*std vector */
typedef std::vector<std::vector<int>>                           vecveci;

/* Useful Eigen typedefs based on the current precision */
typedef Eigen::Matrix<int, 2, 1>                                Vector2i;
typedef Eigen::Matrix<int, 3, 1>                                Vector3i;
typedef Eigen::Matrix<int, 4, 1>                                Vector4i;
typedef Eigen::Matrix<Float, 2, 1>                              Vector2f;
typedef Eigen::Matrix<Float, 3, 1>                              Vector3f;
typedef Eigen::Matrix<Float, 4, 1>                              Vector4f;
typedef Eigen::Matrix<Float, 2, 2>                              Matrix2f;
typedef Eigen::Matrix<Float, 3, 3>                              Matrix3f;
typedef Eigen::Matrix<Float, 4, 4>                              Matrix4f;
typedef Eigen::Matrix<int, Eigen::Dynamic, 1>                   VectorXi;
typedef Eigen::Matrix<bool, Eigen::Dynamic, 1>                  VectorXb;
typedef Eigen::Matrix<Float, Eigen::Dynamic, 1>                 VectorXf;
typedef Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>      MatrixXi;
typedef Eigen::Matrix<Float, Eigen::Dynamic, Eigen::Dynamic>    MatrixXf;
typedef Eigen::Matrix<uint8_t, Eigen::Dynamic, Eigen::Dynamic>  MatrixXu8;
typedef Eigen::SparseMatrix<Float>                              SMatrixf;
typedef Eigen::Triplet<Float>                                   Tripletf;

}  // namespace LibGP
