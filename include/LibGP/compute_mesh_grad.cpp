#include "compute_mesh_grad.h"
#include "compute_face_grad.h"

namespace LibGP {

LIBGP_INLINE void compute_mesh_grad(
    SMatrixf& G, const MatrixXf& V, const MatrixXi& F) {
  std::vector<Matrix3f> Gv;
  compute_mesh_grad(G, Gv, V, F);
}

LIBGP_INLINE void compute_mesh_grad(
    SMatrixf& G, std::vector<Matrix3f>& Gv,
    const MatrixXf& V, const MatrixXi& F) {
  int nf = F.cols();
  int nv = V.cols();
  const Float* pV = V.data();

  Gv.resize(nf);
  G.resize(3 * nf, nv);
  std::vector<Tripletf> coeff(9 * nf);

  #pragma omp parallel for schedule(static)
  for (int i = 0; i < nf; i++) {
    Matrix3f& grad = Gv[i];
    compute_face_grad(grad, pV + 3 * F(0, i),
        pV + 3 * F(1, i), pV + 3 * F(2, i));

    for (int k = 0; k < 3; k++) {
      for (int j = 0; j < 3; j++) {
        coeff[9 * i + 3 * k + j] = Tripletf(3 * i + j, F(k, i), grad(j, k));
      }
    }
  }

  G.reserve(VectorXi::Constant(3 * nf, 3));
  G.setFromTriplets(coeff.begin(), coeff.end());
}

}  // namespace LibGP
