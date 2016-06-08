#pragma once
#include "libgp_global.h"
#include "hash_val.h"

namespace LibGP
{
	class HashVector2i
	{
	public:
		size_t operator() (const Vector2i& v) const
		{
			return hash_val(v[0], v[1]);
		}
	};
	typedef std::unordered_map<Vector2i, Vector2i, HashVector2i> HashEdge;

	LIBGP_INLINE void compute_edge_face_ring(
		HashEdge& E2F, const MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_edge_face_ring.cpp"
#endif