#include "compute_normal.h"
#include "compute_face_normal.h"
#include "normalize_colwise.h"

namespace LibGP {

template <typename DerivedV, typename DerivedF>
LIBGP_INLINE void compute_normal(
    MatrixXf& Nv, MatrixXf& Nf, VectorXf& F_area,
    const Eigen::MatrixBase<DerivedV>& V,
    const Eigen::MatrixBase<DerivedF>& F) {
  compute_face_normal(Nf, F_area, V, F);
  MatrixXf Nfw = Nf * F_area.asDiagonal();

  Nv = MatrixXf::Zero(3, V.cols());
  for (int i = 0; i < F.cols(); i++) {
    for (int j = 0; j < 3; j++) {
      Nv.col(F(j, i)) += Nfw.col(i);
    }
  }

  normalize_colwise(Nv);
}

template <typename DerivedV, typename DerivedF>
LIBGP_INLINE void compute_normal(
    MatrixXf& Nv, MatrixXf& Nf,
    const Eigen::MatrixBase<DerivedV>& V,
    const Eigen::MatrixBase<DerivedF>& F) {
  VectorXf F_area;
  compute_normal(Nv, Nf, F_area, V, F);
}

#ifdef LIBPG_STATIC_LIBRARY
//Explicit template specialization
template<>
void compute_normal<MatrixXf, MatrixXi>(
    MatrixXf&, MatrixXf&, VectorXf&,
    const Eigen::MatrixBase<MatrixXf>&,
    const Eigen::MatrixBase<MatrixXi>&);
void compute_normal<MatrixXf, MatrixXi>(
    MatrixXf&, MatrixXf&,
    const Eigen::MatrixBase<MatrixXf>&,
    const Eigen::MatrixBase<MatrixXi>&);
#endif

}  // namespace LibGP
