#include "speye.h"

namespace LibGP {

LIBGP_INLINE void set_constant(SMatrixf& smat, const Float v) {
  Float* p = smat.valuePtr();
  for (int i = 0; i < smat.nonZeros(); i++) {
    *(p + i) = v;
  }
}

}  // namespace LibGP
