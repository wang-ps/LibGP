#include "delete_pieces.h"
#include "compute_face_ring.h"
#include "delete_faces.h"
#include <queue>

namespace LibGP
{
	LIBGP_INLINE void delete_pieces(MatrixXf& V, MatrixXi& F, int min_num)
	{
		vecveci fring;
		compute_face_ring(fring, F);

		int nf = F.cols();
		VectorXf piece_id = VectorXf::Constant(nf, -2);
		std::vector<int> piece_num;

		/* find all connnected pieces */
		int seed_id = 0;
		while (seed_id != nf)
		{
			// for faces that connected with current seed
			int pid = piece_num.size();
			int np = 0;

			std::queue<int> Q;
			Q.push(seed_id);
			while (!Q.empty())
			{
				int i = Q.front();
				Q.pop();

				// set piece id for this face
				piece_id[i] = pid;
				np++;

				// push un-visited faces into queue
				for (auto fi : fring[i])
				{
					// this is an un-visited face
					if (piece_id[fi] == -2)
					{
						Q.push(fi);
						// set this face as visited
						piece_id[fi] = -1;
					}
				}
			}
			piece_num.push_back(np);

			// find next seed
			seed_id = nf;
			for (int fi = 0; fi < nf; fi++)
			{
				if (piece_id[fi] == -2)
				{
					seed_id = fi;
					break;
				}
			}
		}

		/* mark unvalid faces */
		std::vector<int> unvalid_piece_id;
		for (int i = 0; i < piece_num.size(); i++)
		{
			if (piece_num[i] < min_num)
			{
				unvalid_piece_id.push_back(i);
			}
		}

		VectorXb valid_f = VectorXb::Constant(nf, false);
		for (int i = 0; i < nf; i++)
		{
			bool flag = true;
			for (auto& id : unvalid_piece_id)
			{
				if (piece_id[i] == id)
				{
					flag = false;
					break;
				}
			}
			valid_f[i] = flag;
		}

		/* clean mesh */
		delete_faces(V, F, valid_f);
	}
}