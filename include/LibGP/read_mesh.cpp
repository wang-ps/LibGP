#include "read_mesh.h"
#include "read_obj.h"
#include "read_off.h"

namespace LibGP
{
	LIBGP_INLINE bool read_mesh(std::string filename, MatrixXf& V, MatrixXi& F)
	{
		size_t found = filename.rfind('.');
		if (found != std::string::npos)
		{
			std::string suffix(filename, found + 1);
			if (suffix == "obj")
			{
				read_obj(filename, V, F);
			}
			else if (suffix == "off")
			{
				read_off(filename, V, F);
			}
			else
			{
				cout << "Error : Unsupported file formate!" <<endl;
				return false;
			}
			return true;
		}
		return false;
	}
}
