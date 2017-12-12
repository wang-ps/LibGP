#include "write_ply.h"
#include <rply.h>

namespace LibGP{
	LIBGP_INLINE void write_ply( const std::string &filename,
		const MatrixXf &V, const MatrixXi &F, const MatrixXf &UV, 
		const std::vector<std::string> comments, const MatrixXu8 &C)
	{
		//  create ply 
		p_ply ply = ply_create(filename.c_str(), PLY_LITTLE_ENDIAN, nullptr, 0, nullptr);
		if (!ply) throw std::runtime_error("Unable to write PLY file!");

		// add comments
		for (auto& str : comments)
		{
			ply_add_comment(ply, str.c_str());
		}

		//  add vertex 
		ply_add_element(ply, "vertex", V.cols());
		ply_add_scalar_property(ply, "x", PLY_FLOAT);
		ply_add_scalar_property(ply, "y", PLY_FLOAT);
		ply_add_scalar_property(ply, "z", PLY_FLOAT);

		//  add uv 
		if (UV.size() > 0) {
			ply_add_scalar_property(ply, "u", PLY_FLOAT);
			ply_add_scalar_property(ply, "v", PLY_FLOAT);
			if (UV.cols() != V.cols() || UV.rows() != 2)
				throw std::runtime_error("Texture coordinate matrix has incorrect size");
		}

		//  add color 
		if (C.size() > 0) {
			ply_add_scalar_property(ply, "red", PLY_UCHAR);
			ply_add_scalar_property(ply, "green", PLY_UCHAR);
			ply_add_scalar_property(ply, "blue", PLY_UCHAR);
			if (C.cols() != V.cols() || (C.rows() != 3 && C.rows() != 4))
				throw std::runtime_error("Color matrix has incorrect size");
		}

		//  add face 
		ply_add_element(ply, "face", F.cols());
		ply_add_list_property(ply, "vertex_indices", PLY_UINT8, PLY_INT);
		
		//  write header 
		ply_write_header(ply);

		//  write data 
		for (int j = 0; j < V.cols(); ++j) 
		{
			for (int i = 0; i<V.rows(); ++i)
			{
				ply_write(ply, V(i, j));
			}

			if (UV.size() > 0) 
			{
				for (int i = 0; i<UV.rows(); ++i)
					ply_write(ply, UV(i, j));
			}

			if (C.size() > 0) 
			{
				for (int i = 0; i < C.rows(); ++i)
					ply_write(ply, C(i, j));
			}
		}

		for (int f = 0; f < F.cols(); ++f) 
		{
			ply_write(ply, F.rows());
			for (int i = 0; i < F.rows(); ++i)
			{
				ply_write(ply, F(i, f));			
			}
		}
		
		// close ply
		ply_close(ply);
	}

}
