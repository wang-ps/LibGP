#include <random>

#include "compute_face_normal.h"
#include "compute_face_center.h"

namespace LibGP {

LIBGP_INLINE void sample_points(
    MatrixXf& pts, MatrixXf& normals,
    const MatrixXf& V, const MatrixXi& F, Float area_unit) {
  MatrixXf face_normal, face_center;
  VectorXf areas;
  compute_face_normal(face_normal, areas, V, F);
  compute_face_center(face_center, V, F);
  area_unit *= areas.mean();

  std::default_random_engine generator;
  std::uniform_real_distribution<Float> distribution(0.01, 0.99);

  int nf = F.cols();
  VectorXi point_num(nf);
  int total_pt_num = 0;
  if (area_unit <= 0) area_unit = EPS;
  for (int i = 0; i < nf; ++i) {
    int n = static_cast<int>(areas[i] / area_unit + 0.5);
    if (n == 0) n = 1;
    if (n > 100) n = 100;
    point_num[i] = n;
    total_pt_num += n;
  }

  pts.resize(3, total_pt_num);
  normals.resize(3, total_pt_num);
  for (int i = 0, id = 0; i < nf; ++i) {
    pts.col(id) = face_center.col(i);
    normals.col(id) = face_normal.col(i);

    for (int j = 1; j < point_num[i]; ++j) {
      Float x = 0, y = 0, z = 0;
      while (z < 0.01 || z > 0.99) {
        x = distribution(generator);
        y = distribution(generator);
        z = 1.0 - x - y;
      }
      pts.col(id + j) = x * V.col(F(0, i)) + y * V.col(F(1, i)) + z * V.col(F(2, i));
      normals.col(id + j) = face_normal.col(i);
    }

    id += point_num[i];
  }
}
} // namespace LibGP
