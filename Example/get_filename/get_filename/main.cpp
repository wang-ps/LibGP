#include <LibGP\get_filename.h>
#include <iostream>
using namespace std;

int main()
{
	string filename;
	LibGP::get_filename(filename, false, LibGP::IMAGE_FILE);
	cout << filename << endl;

	return 0;
}