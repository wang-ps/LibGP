#include "bounding_sphere.h"
#include <Miniball.hpp>


namespace LibGP
{
	LIBGP_INLINE void bounding_sphere(
		VectorXf& center, Float& radius, const MatrixXf& V)
	{
		// mini ball interface
		int n = V.cols();
		int d = V.rows();

		if (n < 1) {
			radius = -1;
		}
		else{
			radius = 0;
			center = V.col(0);
		}

		const Float** ap = new const Float*[n];
		for (int i = 0; i < n; ++i)
		{
			ap[i] = V.col(i).data();
		}

		typedef const Float** PointIterator;
		typedef const Float* CoordIterator;
		Miniball::Miniball <
			Miniball::CoordAccessor < PointIterator, CoordIterator >>
			miniball(V.rows(), ap, ap + n);

		// get result
		center.resize(d);
		radius = 0.0;
		if (miniball.is_valid())
		{
			const Float* cnt = miniball.center();
			for (int i = 0; i < d; ++i)
			{
				center[i] = cnt[i];
			}
			radius = sqrt(miniball.squared_radius() + LibGP::EPS);
		}
		else
		{
			// the miniball might failed sometimes
			// if so, just calculate the bounding box
			VectorXf bbmin(d), bbmax(d);
			for (int j = 0; j < d; ++j)
			{
				bbmax[j] = V(j, 0);
				bbmin[j] = V(j, 0);
			}

			for (int i = 1; i < n; ++i)
			{
				for (int j = 0; j < d; ++j)
				{
					if (V(j, i) < bbmin[j]) bbmin[j] = V(j, i);
					if (V(j, i) > bbmax[j]) bbmax[j] = V(j, i);
				}
			}

			VectorXf width(d);
			for (int j = 0; j < d; ++j)
			{
				width[j] = (bbmax[j] - bbmin[j]) / 2.0;
				center[j] = (bbmax[j] + bbmin[j]) / 2.0;
			}

			radius = width[0];
			for (int j = 1; j < d; ++j)
			{
				if (width[j] > radius) radius = width[j];
			}
		}	
		
		//cout << "Computation time was " << miniball.get_time() << " seconds\n";
		delete[] ap;
	}
}
