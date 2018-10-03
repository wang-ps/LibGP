#include "compute_vtx_ring.h"
#include "adj_to_list.h"
#include "compute_vtx_adj.h"

namespace LibGP {

LIBGP_INLINE void compute_vtx_ring(vecveci& vec, const MatrixXi& F) {
  SMatrixf A;
  compute_vtx_adj(A, F);
  adj_to_list(vec, A);
}

}  // namespace LibGP


