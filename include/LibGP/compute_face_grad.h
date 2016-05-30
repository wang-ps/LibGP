#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void compute_face_grad(
		Matrix3f& grad, Float* pv0, Float* pv1, Float* pv2);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_face_grad.cpp"
#endif