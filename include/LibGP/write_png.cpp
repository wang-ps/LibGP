#include "write_png.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace LibGP
{
	LIBGP_INLINE bool write_png(const std::string filename,
	  UINT8 *data, const int width, const int height,
	  const bool flip, const bool alpha)
	{
		// flip
		if (flip)
		{
			for (int j = 0; j < height / 2; ++j)
			{
				for (int i = 0; i < width; ++i)
				{
					UINT8* p = data + 4 * (i + j*width);
					UINT8* q = data + 4 * (i + (height - j - 1)*width);
					for (int k = 0; k < 4; k++)
					{
						UINT8 tmp = p[k];
						p[k] = q[k];
						q[k] = tmp;
					}					
				}
			}				
		}		

		// transparent
		if (!alpha)
		{
			for (int j = 0; j < height; ++j)
			{
				for (int i = 0; i < width; ++i)
				{
					data[4 * (i + j*width) + 3] = 255;
				}
			}
		}

		bool ret = stbi_write_png(filename.c_str(), width, height, 4, data, 0);
		return ret;
	}
}
