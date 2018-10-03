#include "reconstruct_mesh_LS.h"
#include "compute_vtx_face_ring.h"
#include "compute_face_center.h"


namespace LibGP {

LIBGP_INLINE void reconstruct_mesh_LS(
    MatrixXf& V1, const MatrixXf& V,
    const MatrixXi& F, const MatrixXf& N1, int it_num /* = 30 */) {
  // compute vertex_face_ring
  vecveci vf_ring;
  compute_vtx_face_ring(vf_ring, F);

  // update vertex
  reconstruct_mesh_LS(V1, V, F, N1, vf_ring, it_num);
}

LIBGP_INLINE void reconstruct_mesh_LS(
    MatrixXf& V1, const MatrixXf& V,
    const MatrixXi& F, const MatrixXf& N1,
    const vecveci& vf_ring, int it_num /* = 30 */) {
  // init
  V1 = V;

  // iteration
  MatrixXf Fc, V2;
  for (int it = 0; it < it_num; it++) {
    // compute face center
    compute_face_center(Fc, V1, F);

    // update vertex
    V2 = V1;
    #pragma omp parallel for
    for (int i = 0; i < vf_ring.size(); i++) {
      if (vf_ring[i].size() > 0) {
        Eigen::Vector3d vt(0, 0, 0);
        for (const int& fi : vf_ring[i]) {
          vt += N1.col(fi) * (N1.col(fi).dot(Fc.col(fi) - V2.col(i)));
        }
        V1.col(i) += vt / (Float)vf_ring[i].size();
      }
    }
  }
}

}  // namespace LibGP
