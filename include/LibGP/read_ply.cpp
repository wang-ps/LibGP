#include "read_ply.h"

#ifdef USE_RPLY

#include <rply.h>

namespace LibGP {

LIBGP_INLINE bool LibGP::read_ply(std::string filename, MatrixXf& V, MatrixXi& F) {
  // open ply file
  p_ply ply = ply_open(filename.c_str(), nullptr, 0, nullptr);
  if (!ply) {
    std::cout << "Open PLY file error!" << std::endl;
    return false;
  }

  // read file header
  if (!ply_read_header(ply)) {
    ply_close(ply);
    std::cout << "Open PLY header error!" << std::endl;
    return false;
  }
  
  // get vertex number and face number
  p_ply_element element = nullptr;
  uint32_t nv = 0, nf = 0;
  while ((element = ply_get_next_element(ply, element)) != nullptr) {
    const char *name;
    long nInstances;

    ply_get_element_info(element, &name, &nInstances);
    if (!strcmp(name, "vertex"))
      nv = (uint32_t)nInstances;
    else if (!strcmp(name, "face"))
      nf = (uint32_t)nInstances;
  }

  // init F&V
  F.resize(3, nf);
  V.resize(3, nv);

  // callback
  auto rply_vertex_cb = [](p_ply_argument argument) -> int {
    MatrixXf *pV; long index, coord;
    ply_get_argument_user_data(argument, (void **)&pV, &coord);
    ply_get_argument_element(argument, nullptr, &index);
    (*pV)(coord, index) = (Float)ply_get_argument_value(argument);
    return 1;
  };
  auto rply_index_cb = [](p_ply_argument argument) -> int {
    MatrixXi *pF;
    ply_get_argument_user_data(argument, (void **)&pF, nullptr);

    long length, value_index, index;
    ply_get_argument_property(argument, nullptr, &length, &value_index);
    if (length != 3) throw std::runtime_error("Only triangle faces are supported!");
    ply_get_argument_element(argument, nullptr, &index);
    if (value_index >= 0)
      (*pF)(value_index, index) = (int)ply_get_argument_value(argument);

    return 1;
  };

  // set vertex callback
  ply_set_read_cb(ply, "vertex", "x", rply_vertex_cb, &V, 0);
  ply_set_read_cb(ply, "vertex", "y", rply_vertex_cb, &V, 1);
  ply_set_read_cb(ply, "vertex", "z", rply_vertex_cb, &V, 2);

  // set face callback
  long nfr = ply_set_read_cb(ply, "face", "vertex_indices", rply_index_cb, &F, 0);
  if (nfr < 1) ply_set_read_cb(ply, "face", "vertex_index", rply_index_cb, &F, 0);

  //ply_read
  ply_read(ply);
  ply_close(ply);

  return true;
}

}  // namespace LibGP

#else

#include <happly.h>

namespace LibGP {

LIBGP_INLINE bool read_ply(std::string filename, MatrixXf& V, MatrixXi& F) {
  std::ifstream infile(filename, std::ios::binary);
  if (!infile) {
   std::cerr << "Error, cannot read ply files!" << std::endl;
   return false;
  }

  happly::PLYData plyIn(infile);
  std::vector<float> vtx = plyIn.getVertices();
  std::vector<int> faces = plyIn.getTriFaces();

  int nv = vtx.size() / 3;
  int nf = faces.size() / 3;

  V.resize(3, nv);
  F.resize(3, nf);

  std::copy(vtx.begin(), vtx.end(), V.data());
  std::copy(faces.begin(), faces.end(), F.data());

  return true;
}

}  // namespace LibGP

#endif