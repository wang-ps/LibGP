#include "read_mesh.h"
#include "read_obj.h"
#include "read_off.h"


LIBGP_INLINE bool LibGP::read_mesh(std::string filename, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
	size_t found = filename.rfind('.');
	if(found != std::string::npos)
	{
		std::string suffix(filename, found + 1);
		if (suffix == "obj")
		{
			LibGP::read_obj(filename, V, F);
		}
		else if (suffix == "off")
		{
			LibGP::read_off(filename, V, F);
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