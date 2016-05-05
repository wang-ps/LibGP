function V1 = reconstruct_mesh_LS(V, F, N1, lambda )

    if ~exist('lambda', 'var'), lambda = 1.0e-5; end
    
    F2E = compute_edge_face_adj(F);
    [Ei, Ej, Es] = find(F2E);    

    ne = size(Ei, 1);
    nv = size(V, 2);
    i = bsxfun(@plus, repmat(Ei', 3, 1), [0; nv; 2*nv]);
    j = bsxfun(@plus, repmat(Ej', 3, 1), [0; nv; 2*nv]);
    N1 = N1(:, Es);

    Mi = reshape(repmat(1:ne, 6, 1), 6*ne, 1);
    Mj = reshape([i; j], 6*ne, 1);
    Ms = reshape([N1; -N1], 6*ne, 1);    
    M = sparse(Mi, Mj, Ms);

    V1 = (lambda*speye(3*nv) +  (M'* M) ) \ reshape(lambda*V', 3*nv, 1);
    V1 = reshape(V1, nv, 3)';
end