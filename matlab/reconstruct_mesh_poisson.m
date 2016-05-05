function V1 = reconstruct_mesh_poisson(V, F, N1, lambda)

    if ~exist('lambda', 'var'), lambda = 1.0e-10; end

    % pre-compute
    nf = size(F, 2);
    nv = size(V, 2);
    areas = compute_face_area(V, F);
    N = compute_face_normal(V, F);

    % gradient
    Gs = compute_mesh_gradient(V, F);

    % M is weight/"mass" matrix
    M = sparse(1:3*nf,1:3*nf, reshape([areas; areas; areas], 3*nf, 1));

    % compute new gradient
    G1 = Gs*V';
    alpha = acos(dot(N, N1));
    v = cross(N, N1);   
    for i = 1:nf
        R = compute_rotation(v(:, i), alpha(i));
        G1(3*i-2:3*i, :) = R*G1(3*i-2:3*i, :)*R'; 
    end

    L = Gs'*M*Gs + lambda * speye(nv);    
    RHS = Gs'*M*G1 + lambda * V';

    V1 = L \ RHS;
    V1 = V1';
end



