#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <omp.h>
#include <string>
#include <atlstr.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include <Eigen/Dense>
#include <Eigen/Sparse>

/* inline */
#ifndef LIBPG_STATIC_LIBRARY
#  define LIBGP_INLINE inline
#else
#  define LIBGP_INLINE
#endif

using std::cout;
using std::cerr;
using std::endl;

/* Application precision -- can be set to single or Float precision */
#if defined(SINGLE_PRECISION)
typedef float Float;
#else
typedef double Float;
#endif

namespace LibGP{

const Float EPS = 1.0e-10;

/*std vector */
typedef std::vector<std::vector<int>>							vecveci;

/* Useful Eigen typedefs based on the current precision */
typedef Eigen::Matrix<int, 2, 1>  								Vector2i;
typedef Eigen::Matrix<int, 3, 1>  								Vector3i;
typedef Eigen::Matrix<int, 4, 1>								Vector4i;
typedef Eigen::Matrix<Float, 2, 1>								Vector2f;
typedef Eigen::Matrix<Float, 3, 1>								Vector3f;
typedef Eigen::Matrix<Float, 4, 1>								Vector4f;
typedef Eigen::Matrix<Float, 2, 2>								Matrix2f;
typedef Eigen::Matrix<Float, 3, 3>								Matrix3f;
typedef Eigen::Matrix<Float, 4, 4>								Matrix4f;
typedef Eigen::Matrix<int, Eigen::Dynamic, 1>					VectorXi;
typedef Eigen::Matrix<bool, Eigen::Dynamic, 1>  				VectorXb;
typedef Eigen::Matrix<Float, Eigen::Dynamic, 1> 				VectorXf;
typedef Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>		MatrixXi;
typedef Eigen::Matrix<Float, Eigen::Dynamic, Eigen::Dynamic>	MatrixXf;
typedef Eigen::Matrix<UINT8, Eigen::Dynamic, Eigen::Dynamic>	MatrixXu8;
typedef Eigen::SparseMatrix<Float>								SMatrixf;
typedef Eigen::Triplet<Float>									Tripletf;
 
}
