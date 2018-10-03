#include "delete_faces.h"

namespace LibGP {

LIBGP_INLINE void delete_faces(MatrixXf& V,
    MatrixXi& F, const VectorXb& valid_f) {
  int nf = F.cols();
  int nv = V.cols();

  VectorXb valid_v = VectorXb::Constant(nv, false);
  for (int i = 0; i < nf; ++i) {
    if (valid_f[i]) {
      for (int j = 0; j < 3; ++j) {
        valid_v[F(j, i)] = true;
      }
    }
  }

  // valid F idx
  int nvf = 0;
  VectorXi fi = VectorXi::Constant(F.cols(), -1);
  for (int i = 0; i < F.cols(); i++) {
    if (valid_f[i] == 1) {
      fi[i] = nvf++;
    }
  }

  // valid V idx
  int nvv = 0;
  VectorXi vi = VectorXi::Constant(V.cols(), -1);
  for (int i = 0; i < V.cols(); i++) {
    if (valid_v[i]) {
      vi[i] = nvv++;
    }
  }

  // valid F
  for (int i = 0; i < nf; i++) {
    if (valid_f[i]) {
      F.col(fi[i]) << vi[F(0, i)], vi[F(1, i)], vi[F(2, i)];
    }
  }
  F.conservativeResize(3, nvf);

  // valid V
  for (int i = 0; i < nv; i++) {
    if (valid_v[i]) {
      V.col(vi[i]) = V.col(i);
    }
  }
  V.conservativeResize(3, nvv);
}

}  // namespace LibGP