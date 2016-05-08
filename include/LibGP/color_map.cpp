#include "color_map.h"

namespace LibGP
{
	LIBGP_INLINE void color_map(MatrixXu8 &C, const VectorXf &X, ColorMapType colormap)
	{
		color_map(C, X, X.minCoeff(), X.maxCoeff() + EPS, colormap);
	}

	LIBGP_INLINE void color_map(MatrixXu8 &C, const std::vector<Float> &X, ColorMapType colormap)
	{
		Eigen::Map<const VectorXf> X1(X.data(), X.size());
		color_map(C, X1, colormap);
	}

	LIBGP_INLINE void color_map(MatrixXu8 &C, const VectorXf &X, Float min, Float max, ColorMapType colormap)
	{
		for (int i = 0; i < X.size(); ++i)
		{
			Float r, g, b;
			if (colormap == JET)
			{
				jet(r, g, b, (X[i] - min) / (max - min));
			}
			else
			{
				rain_bow(r, g, b, (X[i] - min) / (max - min));
			}
			C.col(i) << UINT8(r*255.0), UINT8(g*255.0), UINT8(b*255.0);
		}
	}

	LIBGP_INLINE void jet(Float &r, Float &g, Float &b, Float x)
	{
		const Float rone = 0.8f, gone = 1.0f, bone = 1.0f;

		x = max(min(x, 1.0), 0.0);
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

	LIBGP_INLINE void rain_bow(Float &r, Float &g, Float &b, Float x)
	{
		x = max(min(x, 1.0), 0.0);
		if (x < 0.25)
		{
			r = 0.0;
			g = 4.0*x;
			b = 1.0;
		}
		else if (x < 0.5)
		{
			r = 0.0;
			g = 1.0;
			b = -4.0*(x - 0.5);
		}
		else if (x < 0.75)
		{
			r = 4.0*(x - 0.5);
			g = 1.0;
			b = 0.0;
		}
		else
		{
			r = 1.0;
			g = -4.0*(x - 1);
			b = 0;
		}
	}
}