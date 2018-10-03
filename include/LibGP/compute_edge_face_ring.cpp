#include "compute_edge_face_ring.h"

namespace LibGP {

LIBGP_INLINE void compute_edge_face_ring(
    HashEdge& E2F, const MatrixXi& F) {
  const int nv = F.maxCoeff() + 1;
  // V + F - E = 2 - 2*g
  E2F.reserve(nv + F.cols() + 100);

  for (int i = 0; i < F.cols(); i++) {
    for (int j = 0; j < 3; j++) {
      int v0 = F(j, i), v1 = F((j + 1) % 3, i);

      // ensure : v0 <= v1
      int ei = 0, key = 0;
      if (v0 > v1) {
        ei = 1;
        std::swap(v0, v1);
      }

      //// insert
      //auto it = E2F.find(key);
      //if (it == E2F.end())
      //{
      //	auto tpair = E2F.emplace(key, Vector2i(-1, -1));
      //	it = tpair.first;
      //}
      //// modify value
      //it->second[ei] = i;

      // try to insert
      auto tpair = E2F.emplace(Vector2i(v0, v1), Vector2i(-1, -1));
      // modify value
      (*tpair.first).second[ei] = i;
    }
  }
}

}  // namespace LibGP
