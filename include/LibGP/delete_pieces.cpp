#include "delete_pieces.h"
#include "compute_face_ring.h"
#include "delete_faces.h"
#include <queue>

namespace LibGP {

void delete_pieces(MatrixXf& V, MatrixXi& F, int min_num) {
  vecveci fring;
  compute_face_ring(fring, F);

  int nf = F.cols();
  VectorXf piece_id = VectorXf::Constant(nf, -2);
  std::vector<int> piece_num;

  /* find all connnected pieces */
  int seed_id = 0;
  while (seed_id != nf) {
    // for faces that connected with current seed
    int pid = piece_num.size();
    int np = 0;

    std::queue<int> Q;
    Q.push(seed_id);
    while (!Q.empty()) {
      int i = Q.front();
      Q.pop();

      // set piece id for this face
      piece_id[i] = pid;
      np++;

      // push un-visited faces into queue
      for (auto fi : fring[i]) {
        // this is an un-visited face
        if (piece_id[fi] == -2) {
          Q.push(fi);
          // set this face as visited
          piece_id[fi] = -1;
        }
      }
    }
    piece_num.push_back(np);

    // find next seed
    seed_id = nf;
    for (int fi = 0; fi < nf; fi++) {
      if (piece_id[fi] == -2) {
        seed_id = fi;
        break;
      }
    }
  }

  /* mark invalid faces */
  vector<int> invalid_piece_id;
  //// version 1: keep the component with the largest face number
  //if (min_num < 0) {
  //  min_num = *std::max_element(piece_num.begin(), piece_num.end());
  //}
  //for (int i = 0; i < piece_num.size(); i++) {
  //  if (piece_num[i] < min_num) {
  //    invalid_piece_id.push_back(i);
  //  }
  //}
  //// end of version 1

  // version 2: keep the largest component
  int num = piece_num.size();
  MatrixXf bbox_min = MatrixXf::Constant(3, num, std::numeric_limits<float>::max());
  MatrixXf bbox_max = MatrixXf::Constant(3, num, -std::numeric_limits<float>::max());
  for (int i = 0; i < nf; i++) {
    int id = piece_id[i];
    for (int j = 0; j < 3; ++j) {
      int fi = F(j, i);
      for (int k = 0; k < 3; ++k) {
        float val = V(k, fi);
        if (val < bbox_min(k, id)) bbox_min(k, id) = val;
        if (val > bbox_max(k, id)) bbox_max(k, id) = val;
      }
    }
  }
  VectorXf bbox_width = (bbox_max - bbox_min).colwise().maxCoeff();
  int max_id = 0;
  float max_width = bbox_width[0];
  for (int i = 1; i < num; ++i) {
    if (bbox_width[i] > max_width) {
      max_width = bbox_width[i];
      max_id = i;
    }
  }
  for (int i = 0; i < num; ++i) {
    if (i != max_id) invalid_piece_id.push_back(i);
  }  
  // end of version 2


  VectorXb valid_f = VectorXb::Constant(nf, false);
  for (int i = 0; i < nf; i++) {
    bool flag = true;
    for (auto& id : invalid_piece_id) {
      if (piece_id[i] == id) {
        flag = false;
        break;
      }
    }
    valid_f[i] = flag;
  }

  /* clean mesh */
  delete_faces(V, F, valid_f);
}

}  // namespace LibGP