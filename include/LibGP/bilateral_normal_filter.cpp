#include "bilateral_normal_filter.h"
#include "compute_face_ringv.h"
#include "compute_avg_edge_length.h"
#include "compute_face_center.h"
#include "compute_face_normal.h"
#include "reconstruct_mesh_LS.h"

namespace LibGP {

LIBGP_INLINE void bilateral_normal_filter(
    MatrixXf& V1, const MatrixXf& V, const MatrixXi& F,
    Float sigma_r, Float sigma_s, int it_n, int it_v) {
  vecveci fring;
  compute_face_ringv(fring, F);

  V1 = V;
  Float avg_edge_len;
  VectorXf f_area;
  MatrixXf N, N1, Nw, f_center;
  for (int it = 0; it < it_n; ++it) {
    // update N, f_center and avg_edge_len
    bool update = !(it % 5);
    if (update) {
      compute_face_center(f_center, V1, F);
      compute_face_normal(N, f_area, V1, F);
      avg_edge_len = compute_avg_edge_length(V, F);
    }

    Nw = N * f_area.asDiagonal();
    N1.setZero(3, N.cols());

    Float sr = -0.5 / pow(sigma_r, 2);
    Float ss = -0.5 / pow(sigma_s * avg_edge_len, 2);

    // weighted average to update normal
    #pragma omp parallel for
    for (int i = 0; i < fring.size(); i++) {
      for (const auto& j : fring[i]) {
        N1.col(i) += Nw.col(j) *
            exp((f_center.col(i) - f_center.col(j)).squaredNorm() * ss) *
            exp((N.col(i) - N.col(j)).squaredNorm() * sr);
      }
      Float d = N1.col(i).norm();
      if (d < EPS) d = EPS;
      N1.col(i) /= d;
    }
    N = N1;

    //update V1
    if ((update && it > 0) || it == it_n - 1) {
      reconstruct_mesh_LS(V1, V, F, N1);
    }
  }
}

}  // namespace LibGP