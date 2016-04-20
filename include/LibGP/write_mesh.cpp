#include "write_mesh.h"
#include "write_obj.h"
#include "write_off.h"

namespace LibGP{
	LIBGP_INLINE bool write_mesh(std::string filename, const MatrixXf& V, const MatrixXi& F)
	{
		size_t found = filename.rfind('.');
		if (found != std::string::npos)
		{
			std::string suffix(filename, found + 1);
			if (suffix == "obj")
			{
				write_obj(filename, V, F);
			}
			else if (suffix == "off")
			{
				write_off(filename, V, F);
			}
			else
			{
				std::cout << "Error : Unsupported file formate!" << std::endl;
				return false;
			}

			return true;
		}
		return false;
	}
}
