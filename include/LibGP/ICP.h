#pragma once
#include "libgp_global.h"
#include "KDTreeAdaptor.h"
#include <nanoflann.hpp>

namespace LibGP {

	/* Compute the rigid motion for point-to-point and point-to-plane distances */
	namespace RigidMotionEstimator {
		// @param Source (one 3D point per column)
		// @param Target (one 3D point per column)
		// @param Confidence weights
		template <typename Derived1, typename Derived2, typename Derived3>
		Eigen::Affine3d point_to_point(Eigen::MatrixBase<Derived1>& X,
			Eigen::MatrixBase<Derived2>& Y,
			const Eigen::MatrixBase<Derived3>& w)
		{
			// Normalize weight vector
			Eigen::VectorXd w_normalized = w / w.sum();
			// De-mean
			Eigen::Vector3d X_mean, Y_mean;
			for (int i = 0; i < 3; ++i) {
				X_mean(i) = (X.row(i).array()*w_normalized.transpose().array()).sum();
				Y_mean(i) = (Y.row(i).array()*w_normalized.transpose().array()).sum();
			}
			X.colwise() -= X_mean;
			Y.colwise() -= Y_mean;
			// Compute transformation
			Eigen::Affine3d transformation;
			Eigen::Matrix3d sigma = X * w_normalized.asDiagonal() * Y.transpose();
			Eigen::JacobiSVD<Eigen::Matrix3d> svd(sigma, Eigen::ComputeFullU | Eigen::ComputeFullV);
			if (svd.matrixU().determinant()*svd.matrixV().determinant() < 0.0) {
				Eigen::Vector3d S = Eigen::Vector3d::Ones(); S(2) = -1.0;
				transformation.linear().noalias() = svd.matrixV()*S.asDiagonal()*svd.matrixU().transpose();
			}
			else {
				transformation.linear().noalias() = svd.matrixV()*svd.matrixU().transpose();
			}
			transformation.translation().noalias() = Y_mean - transformation.linear()*X_mean;
			// Apply transformation
			X = transformation*X;
			// Re-apply mean
			X.colwise() += X_mean;
			Y.colwise() += Y_mean;
			// Return transformation
			return transformation;
		}
		// @param Source (one 3D point per column)
		// @param Target (one 3D point per column)
		template <typename Derived1, typename Derived2>
		inline Eigen::Affine3d point_to_point(Eigen::MatrixBase<Derived1>& X,
			Eigen::MatrixBase<Derived2>& Y)
		{
			return point_to_point(X, Y, Eigen::VectorXd::Ones(X.cols()));
		}

		// @param Source (one 3D point per column)
		// @param Target (one 3D point per column)
		// @param Target normals (one 3D normal per column)
		// @param Confidence weights
		// @param Right hand side
		template <typename Derived1, typename Derived2, typename Derived3, typename Derived4, typename Derived5>
		Eigen::Affine3d point_to_plane(Eigen::MatrixBase<Derived1>& X,
			Eigen::MatrixBase<Derived2>& Y,
			Eigen::MatrixBase<Derived3>& N,
			const Eigen::MatrixBase<Derived4>& w,
			const Eigen::MatrixBase<Derived5>& u)
		{
			typedef Eigen::Matrix<double, 6, 6> Matrix66;
			typedef Eigen::Matrix<double, 6, 1> Vector6;
			typedef Eigen::Block<Matrix66, 3, 3> Block33;
			// Normalize weight vector
			Eigen::VectorXd w_normalized = w / w.sum();
			// De-mean
			Eigen::Vector3d X_mean;
			for (int i = 0; i < 3; ++i)
				X_mean(i) = (X.row(i).array()*w_normalized.transpose().array()).sum();
			X.colwise() -= X_mean;
			Y.colwise() -= X_mean;
			// Prepare LHS and RHS
			Matrix66 LHS = Matrix66::Zero();
			Vector6 RHS = Vector6::Zero();
			Block33 TL = LHS.topLeftCorner<3, 3>();
			Block33 TR = LHS.topRightCorner<3, 3>();
			Block33 BR = LHS.bottomRightCorner<3, 3>();
			Eigen::MatrixXd C = Eigen::MatrixXd::Zero(3, X.cols());
			#pragma omp parallel
			{
				#pragma omp for
				for (int i = 0; i < X.cols(); i++) {
					C.col(i) = X.col(i).cross(N.col(i));
				}
				#pragma omp sections nowait
				{
					#pragma omp section
					for (int i = 0; i < X.cols(); i++) TL.selfadjointView<Eigen::Upper>().rankUpdate(C.col(i), w(i));
					#pragma omp section
					for (int i = 0; i < X.cols(); i++) TR += (C.col(i)*N.col(i).transpose())*w(i);
					#pragma omp section
					for (int i = 0; i < X.cols(); i++) BR.selfadjointView<Eigen::Upper>().rankUpdate(N.col(i), w(i));
					#pragma omp section
					for (int i = 0; i < C.cols(); i++) {
						double dist_to_plane = -((X.col(i) - Y.col(i)).dot(N.col(i)) - u(i))*w(i);
						RHS.head<3>() += C.col(i)*dist_to_plane;
						RHS.tail<3>() += N.col(i)*dist_to_plane;
					}
				}
			}
			LHS = LHS.selfadjointView<Eigen::Upper>();
			// Compute transformation
			Eigen::Affine3d transformation;
			Eigen::LDLT<Matrix66> ldlt(LHS);
			RHS = ldlt.solve(RHS);
			transformation = Eigen::AngleAxisd(RHS(0), Eigen::Vector3d::UnitX()) *
				Eigen::AngleAxisd(RHS(1), Eigen::Vector3d::UnitY()) *
				Eigen::AngleAxisd(RHS(2), Eigen::Vector3d::UnitZ());
			transformation.translation() = RHS.tail<3>();
			// Apply transformation
			X = transformation*X;
			// Re-apply mean
			X.colwise() += X_mean;
			Y.colwise() += X_mean;
			// Return transformation
			return transformation;
		}
		// @param Source (one 3D point per column)
		// @param Target (one 3D point per column)
		// @param Target normals (one 3D normal per column)
		// @param Confidence weights
		template <typename Derived1, typename Derived2, typename Derived3, typename Derived4>
		inline Eigen::Affine3d point_to_plane(Eigen::MatrixBase<Derived1>& X,
			Eigen::MatrixBase<Derived2>& Yp,
			Eigen::MatrixBase<Derived3>& Yn,
			const Eigen::MatrixBase<Derived4>& w)
		{
			return point_to_plane(X, Yp, Yn, w, Eigen::VectorXd::Zero(X.cols()));
		}
	}

	// ICP implementation using iterative reweighting
	namespace ICP {

		struct Parameters
		{
			Parameters(): max_icp(100),	stop(1e-5) {}
			int max_icp;    // max ICP iteration
			double stop;    // stopping criteria
		};

		struct sort_pred {
			bool operator()(const std::pair<int, double> &left,
			const std::pair<int, double> &right) {
				return left.second < right.second;
			}
		};
		// @param Residuals
		// @param Parameter
		void trimmed_weight(Eigen::VectorXd& r, double p) {
			std::vector<std::pair<int, double> > sortedDist(r.rows());
			for (int i = 0; i < r.rows(); ++i) {
				sortedDist[i] = std::pair<int, double>(i, r(i));
			}
			std::sort(sortedDist.begin(), sortedDist.end(), sort_pred());
			r.setZero();
			int nbV = r.rows()*p;
			for (int i = 0; i < nbV; ++i) {
				r(sortedDist[i].first) = 1.0;
			}
		}

		// ICP with point to point
		// @param Source (one 3D point per column)
		// @param Target (one 3D point per column)
		// @param Parameters
		void point_to_point(MatrixXf& X, MatrixXf& Y, Parameters par = Parameters()) 
		{
			// Build kd-tree
			LibGP::KDTreeAdaptor<MatrixXf> kdtree(Y);
			
			// Buffers
			MatrixXf Q = MatrixXf::Zero(3, X.cols());
			VectorXf W = VectorXf::Ones(X.cols());
			Eigen::Matrix3Xd Xo1 = X;

			// ICP
			for (int icp = 0; icp < par.max_icp; ++icp) 
			{
				// Find closest point
				#pragma omp parallel for
				for (int i = 0; i < X.cols(); ++i) 
				{
					__int64 out_idx = 0;
					Float out_dist = 0.0;
					kdtree.closest(X.col(i).data(), &out_idx, &out_dist);
					Q.col(i) = Y.col(out_idx);
				}

				// Computer rotation and translation
				// Rotation and translation update
				RigidMotionEstimator::point_to_point(X, Q, W);
				// Stopping criteria
				Float stop = (X - Xo1).colwise().norm().maxCoeff();
				Xo1 = X;
				if (stop < par.stop) break;
			}
		}

		// Reweighted ICP with point to plane
		// @param Source (one 3D point per column)
		// @param Target (one 3D point per column)
		// @param Target normals (one 3D normal per column)
		// @param Parameters
		void point_to_plane(MatrixXf& X, MatrixXf& Y, MatrixXf& N, Parameters par = Parameters())
		{
			// Build kd-tree
			LibGP::KDTreeAdaptor<MatrixXf> kdtree(Y);

			// Buffers
			Eigen::Matrix3Xd Qp = Eigen::Matrix3Xd::Zero(3, X.cols());
			Eigen::Matrix3Xd Qn = Eigen::Matrix3Xd::Zero(3, X.cols());
			Eigen::VectorXd W = Eigen::VectorXd::Ones(X.cols());
			Eigen::Matrix3Xd Xo1 = X;
			
			// ICP
			for (int icp = 0; icp < par.max_icp; ++icp)
			{
				// Find closest point
				#pragma omp parallel for
				for (int i = 0; i < X.cols(); ++i) {
					__int64 out_idx = 0;
					Float out_dist = 0.0;
					kdtree.closest(X.col(i).data(), &out_idx, &out_dist);

					Qp.col(i) = Y.col(out_idx);
					Qn.col(i) = N.col(out_idx);
				}

				// Computer rotation and translation
				RigidMotionEstimator::point_to_plane(X, Qp, Qn, W);
				// Stopping criteria
				double stop = (X - Xo1).colwise().norm().maxCoeff();
				Xo1 = X;
				if (stop < par.stop) break;
			}
		}
	}

}

