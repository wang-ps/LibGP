#include "read_mesh.h"
#include "read_obj.h"
#include "read_off.h"
#include "read_ply.h"

namespace LibGP
{
	LIBGP_INLINE bool read_mesh(std::string filename, MatrixXf& V, MatrixXi& F)
	{
		size_t found = filename.rfind('.');
		if (found != std::string::npos)
		{
			std::string suffix(filename, found + 1);
			std::transform(suffix.begin(), suffix.end(), suffix.begin(), tolower);
			
			bool succ = false;
			if (suffix == "obj")
			{
				succ = read_obj(filename, V, F);
			}
			else if (suffix == "off")
			{
				succ = read_off(filename, V, F);
			}
			else if (suffix == "ply")
			{
				succ = read_ply(filename, V, F);
			}
			else
			{
				cout << "Error : Unsupported file formate!" <<endl;
			}
			return succ;
		}
		return false;
	}
}
