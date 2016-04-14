#pragma once
#include <Eigen/dense>
#include <vector>


inline Float calc_avg_edge_length(Mesh& mesh)
{
	Float le = 0;
	for (auto eh : mesh.edges())
	{
		Mesh::HalfedgeHandle heh = mesh.halfedge_handle(eh, 1);
		Mesh::Point pt1 = mesh.point(mesh.from_vertex_handle(heh));
		Mesh::Point pt2 = mesh.point(mesh.to_vertex_handle(heh));
		le += (pt1 - pt2).norm();
	}
	le /= (Float)mesh.n_edges();
	return le;
}

inline void calc_face_center(Mesh& mesh, MatrixXf& f_center)
{
	f_center.resize(3, mesh.n_faces());
	for (auto fh : mesh.faces())
	{
		Mesh::Point pt(0, 0, 0);
		for (auto fv : mesh.fv_range(fh))
		{
			pt += mesh.point(fv);
		}
		for (int i = 0; i < 3; i++)
		{
			int fi = fh.idx();
			f_center(i, fi) = pt[i] / 3.0;
		}
	}
}

inline void calc_face_normal(Mesh& mesh, MatrixXf& N, VectorXf& f_areas)
{
	N.resize(3, mesh.n_faces());
	f_areas.resize(mesh.n_faces());

	for (auto fh : mesh.faces())
	{
		int fi = fh.idx(), k = 0;
		Mesh::Point p[3];
		for (auto fv : mesh.fv_range(fh))
		{
			p[k++] = mesh.point(fv);
		}
		Mesh::Point n = cross(p[1] - p[0], p[2] - p[0]);

		Float d = n.norm();
		if (d > ESP) n /= d;

		f_areas[fi] = d*0.5;
		for (int i = 0; i < 3; i++)
		{
			N(i, fi) = n[i];
		}
	}
}

inline void calc_face_normal(Mesh& mesh, MatrixXf& N)
{
	VectorXf f_areas;
	calc_face_normal(mesh, N, f_areas);
}

inline void reconstruct_mesh(Mesh& mesh, MatrixXf& N, Mesh& mesh1, int it_num)
{
	// get V
	MatrixXf V(3, mesh.n_vertices());
	for (auto vh : mesh.vertices())
	{
		Mesh::Point &pt = mesh.point(vh);
		for (int i = 0; i < 3; i++)
		{
			V(i, vh.idx()) = pt[i];
		}
	}

	// get F
	MatrixXi F(3, mesh.n_faces());
	for (auto fh : mesh.faces())
	{
		int i = 0;
		for (auto fv : mesh.fv_range(fh))
		{
			F(i++, fh.idx()) = fv.idx();
		}
	}

	for (int it = 0; it < it_num; it++)
	{
		// calc face centers
		MatrixXf Fc = MatrixXf::Zero(3, mesh.n_faces());
#pragma omp parallel for
		for (int i = 0; i < mesh.n_faces(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Fc.col(i) += V.col(F(j, i));
			}
			Fc.col(i) /= 3.0;
		}

		// update vertex
#pragma omp parallel for
		for (int i = 0; i < mesh.n_vertices(); i++)
		{
			Float degree = 0.0;
			Eigen::Vector3d vt(0, 0, 0);
			for (auto vf : mesh.vf_range(mesh.vertex_handle(i)))
			{
				int fi = vf.idx();
				degree += 1;
				vt += N.col(fi) * (N.col(fi).dot(Fc.col(fi) - V.col(i)));
			}
			V.col(i) += vt / degree;
		}
	}

	// output
	mesh1 = mesh;
	for (int i = 0; i < mesh.n_vertices(); i++)
	{
		Mesh::VHandle vh = mesh1.vertex_handle(i);
		mesh1.set_point(vh, Mesh::Point(V(0, i), V(1, i), V(2, i)));
	}
}
