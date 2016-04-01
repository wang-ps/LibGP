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

#include <Eigen/Dense>
#include <Eigen/Sparse>

#ifndef LIBPG_STATIC_LIBRARY
#  define LIBGP_INLINE inline
#else
#  define LIBGP_INLINE
#endif

namespace LibGP{
const double EPS = 1.0e-10;

typedef Eigen::Matrix<bool, Eigen::Dynamic, 1> VectorXb;
}
