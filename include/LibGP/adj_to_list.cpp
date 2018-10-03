#include "adj_to_list.h"

namespace LibGP {

LIBGP_INLINE void LibGP::adj_to_list(
    vecveci& vec, const SMatrixf& A) {
  vec.resize(A.cols());
  for (int k = 0; k < A.outerSize(); ++k) {
    for (SMatrixf::InnerIterator it(A, k); it; ++it) {
      if (it.row() != it.col()) vec[k].push_back(it.row());
    }
  }
}

}  // namespace LibGP
