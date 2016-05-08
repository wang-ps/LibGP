
% compile
mex read_obj.cpp COMPFLAGS="$COMPFLAGS /openmp"
mex write_obj.cpp COMPFLAGS="$COMPFLAGS /openmp"

EigenDir = 'D:\Projects\ThirdLib\Eigen';
LibGPDir = '..\include';
cmd = ['mex reconstruct_mesh_local.cpp COMPFLAGS="$COMPFLAGS /openmp" ' ...
    '-I' EigenDir ' -I' LibGPDir];
eval(cmd);