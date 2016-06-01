function [N, Nf, areas] = compute_normal(V, F)
% compute_normal - compute the normal of a triangulation
%
%   [normal,normalf] = compute_normal(vertex,face);
%
%   normal(i,:) is the normal at vertex i.
%   normalf(j,:) is the normal at face j.


	Nw = cross( V(:,F(2,:))-V(:,F(1,:)), V(:,F(3,:))-V(:,F(1,:)));
	
	d = sqrt( sum(Nw.^2) ); 
	areas = 0.5*d;
	d(d<eps) = eps;
	Nf =  bsxfun(@rdivide, Nw, d);

	N = zeros(3, size(V, 2));
	for i = 1:size(F, 2)
	    N(:, F(:, i)) = N(:, F(:, i)) + repmat(Nw(:, i), 1, 3);
	end
	d = sqrt( sum(N.^2,1) ); 
	d(d<eps) = eps;
	N = bsxfun(@rdivide, N, d);

end