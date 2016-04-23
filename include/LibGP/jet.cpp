#include "jet.h"

namespace LibGP
{
	LIBGP_INLINE void jet(MatrixXf &C, const VectorXf &X)
	{
		jet(C, X, X.minCoeff(), X.maxCoeff() + EPS);
	}

	LIBGP_INLINE void jet(MatrixXf &C, const std::vector<Float> &X)
	{
		Eigen::Map<const VectorXf> X1(X.data(), X.size());
		jet(C, X1);
	}

	LIBGP_INLINE void jet(MatrixXf &C, const VectorXf &X, Float min, Float max)
	{
		for (int i = 0; i < X.size(); ++i)
		{
			Float r, g, b;
			jet(r, g, b, (X[i] - min) / (max - min));
			C.col(i) << r, g, b;
		}
	}

	LIBGP_INLINE void jet(Float &r, Float &g, Float &b, Float x)
	{
		const Float rone = 0.8f, gone = 1.0f, bone = 1.0f;

		x = std::max(std::min(x, 1.0), 0.0);
		if (x < 1.0 / 8.0) 
		{
			r = 0;
			g = 0;
			b = bone * (0.5 + x / (1.0 / 8.0) * 0.5);
		}
		else if (x < 3.0 / 8.0) 
		{
			r = 0;
			g = gone * (x - 1.0 / 8.0) / (3.0 / 8.0 - 1.0 / 8.0);
			b = bone;
		}
		else if (x < 5.0 / 8.0) 
		{
			r = rone * (x - 3.0 / 8.0) / (5.0 / 8.0 - 3.0 / 8.0);
			g = gone;
			b = (bone - (x - 3.0 / 8.0) / (5.0 / 8.0 - 3.0 / 8.0));
		}
		else if (x < 7.0 / 8.0) 
		{
			r = rone;
			g = (gone - (x - 5.0 / 8.0) / (7.0 / 8.0 - 5.0 / 8.0));
			b = 0;
		}
		else 
		{
			r = (rone - (x - 7.0 / 8.0) / (1.0 - 7.0 / 8.0) * .5);
			g = 0;
			b = 0;
		}    
	}
}