#include "write_mesh.h"
#include "write_obj.h"
#include "write_off.h"

LIBGP_INLINE bool LibGP::write_mesh(std::string filename, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
	size_t found = filename.rfind('.');
	if (found != std::string::npos)
	{
		std::string suffix(filename, found + 1);
		if (suffix == "obj")
		{
			LibGP::write_obj(filename, V, F);
		}
		else if (suffix == "off")
		{
			LibGP::write_off(filename, V, F);
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