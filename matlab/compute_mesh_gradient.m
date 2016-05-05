function [Gs, G] = compute_mesh_gradient(V, F)
% compute a gradient matrix

	e1 = V(:,F(2,:))-V(:,F(1,:));
	e2 = V(:,F(3,:))-V(:,F(2,:));
	e3 = V(:,F(1,:))-V(:,F(3,:));

	N = cross(e1, e2);
	d2 = sum(N.^2, 1); % may cause divide by zero 

	% compute gradient matrix
	nf = size(F, 2);
	G = zeros(3, 3, nf);
	G(:, 1, :) = bsxfun(@rdivide, cross(N, e2), d2);
	G(:, 2, :) = bsxfun(@rdivide, cross(N, e3), d2);
	G(:, 3, :) = bsxfun(@rdivide, cross(N, e1), d2);

	% construct sparse matrix
	i = repmat(reshape(1:3*nf, 3, 1, nf), 1, 3);
	j = repmat(reshape(double(F), 1, 3, nf), 3, 1);
	Gs = sparse(reshape(i, 9*nf, 1), reshape(j, 9*nf, 1), reshape(G, 9*nf, 1));

end