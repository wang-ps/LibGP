#include "list_to_adj.h"

namespace LibGP {

LIBGP_INLINE void list_to_adj(SMatrixf& A, const vecveci& vec) {
  int jmax = 0;
  std::vector<Tripletf> coeff;
  for (int i = 0; i < vec.size(); i++) {
    for (const int& j : vec[i]) {
      if (j > jmax) jmax = j;
      coeff.push_back(Tripletf(i, j, 1));
    }
  }

  A.resize(vec.size(), jmax + 1);
  A.reserve(coeff.size());
  A.setFromTriplets(coeff.begin(), coeff.end());
}

}  // namespace LibGP
