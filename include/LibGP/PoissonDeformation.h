#pragma once
#include "libgp_global.h"
#include "compute_mesh_grad.h"
#include "compute_face_grad.h"
#include "compute_face_normal.h"
#include "speye.h"

namespace LibGP {

class PoissonDeformation {
 public:
  PoissonDeformation(const MatrixXf& V, const MatrixXi& F, const Float l = 1.0e-4) :
    solver_ready_(false), lamdbda_(l), V_(V), F_(F) {
    setup_solver();
  }

  inline void setup_solver() {
    if (solver_ready_) return;

    compute_mesh_grad(G_, V_, F_);
    compute_mass_matrix();
    SMatrixf I;
    speye(I, V_.cols(), lamdbda_);

    //SMatrixf L = SMatrixf(G_.transpose())*M_*G_ + I;
    SMatrixf L = G_.transpose() * M_ * G_ + I;

    solver_.compute(L);
    solver_ready_ = (solver_.info() == Eigen::Success);
  }

  inline bool deform(MatrixXf& V1, const MatrixXf& N1) {
    if (!solver_ready_) return false;
    std::vector<Matrix3f> Rots;
    compute_rotation(Rots, N1);
    return deform(V1, Rots);
  }

  inline bool deform(MatrixXf& V1, const std::vector<Matrix3f>& Rots) {
    if (!solver_ready_) return false;
    V1 = V_;

    // re-compute gradient
    int nf = F_.cols();
    MatrixXf Gv(3 * nf, 3);
    #pragma omp parallel for // schedule(static)
    for (int i = 0; i < nf; i++) {
      // Apply rotation
      Matrix3f v;
      for (int j = 0; j < 3; j++) {
        v.col(j) = V_.col(F_(j, i));
      }
      v = Rots[i] * v;

      // calc gradient
      Matrix3f grad;
      Float* pv = v.data();
      compute_face_grad(grad, pv, pv + 3, pv + 6);

      grad *= v.transpose();
      Gv.block(3 * i, 0, 3, 3) = grad;
    }

    // slove deformation
    //MatrixXf B = SMatrixf(G_.transpose())*M_*Gv + lamdbda_ * V_.transpose();
    MatrixXf B = G_.transpose() * M_ * Gv + lamdbda_ * V_.transpose();

    V1 = solver_.solve(B).transpose();

    return	solver_.info() == Eigen::Success;
  }

 private:
  inline void compute_mass_matrix() {
    VectorXf face_areas_;
    compute_face_normal(Nf_, face_areas_, V_, F_);
    // NORMALIZE FACE_AREA
    face_areas_ /= face_areas_.mean();

    int nf = F_.cols();
    M_.resize(3 * nf, 3 * nf);
    M_.reserve(VectorXi::Constant(3 * nf, 1));
    for (int i = 0; i < nf; i++) {
      for (int j = 0; j < 3; j++) {
        M_.insert(3 * i + j, 3 * i + j) = face_areas_[i];
      }
    }
  }

  inline void compute_rotation(std::vector<Matrix3f>& Rots, const MatrixXf& N1) {
    int nf = N1.cols();
    Rots.resize(nf);
    #pragma omp parallel for // schedule(static)
    for (int i = 0; i < nf; i++) {
      Vector3f n0 = Nf_.col(i);
      Vector3f n1 = N1.col(i);

      // compute rotation
      Vector3f axis = n0.cross(n1);
      Float d = axis.norm();
      axis = d < EPS ? Eigen::Vector3d(0, 0, 1) : axis / d;

      Float dot01 = n0.dot(n1);
      if (dot01 < -1)dot01 = -1;
      if (dot01 > 1)dot01 = 1;
      Float angle = acos(dot01);
      Rots[i] = Eigen::AngleAxis<Float>(angle, axis);
    }
  }

 private:
  Eigen::SimplicialLDLT<SMatrixf> solver_;
  bool solver_ready_;
  const Float lamdbda_;
  const MatrixXf& V_;
  const MatrixXi& F_;
  MatrixXf Nf_;

  SMatrixf G_;
  SMatrixf M_;
};

}  // namespace LibGP