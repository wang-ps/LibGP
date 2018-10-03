#include "compute_vtx_adj.h"
#include "set_constant.h"

namespace LibGP {

LIBGP_INLINE void compute_vtx_adj(SMatrixf& A, const MatrixXi& F) {
  std::vector<Tripletf> coeff;
  coeff.reserve(3 * F.cols());
  for (int i = 0; i < F.cols(); i++) {
    coeff.push_back(Tripletf(F(0, i), F(1, i), 1.0));
    coeff.push_back(Tripletf(F(1, i), F(2, i), 1.0));
    coeff.push_back(Tripletf(F(2, i), F(0, i), 1.0));
  }

  int nv = F.maxCoeff() + 1;
  SMatrixf T(nv, nv);
  T.setFromTriplets(coeff.begin(), coeff.end());

  // VERY IMPORTANT : deal with boundary vertex
  A = SMatrixf(T.transpose()) + T;

  // set all non-zero to 1
  set_constant(A, 1.0);
}

}  // namespace LibGP
