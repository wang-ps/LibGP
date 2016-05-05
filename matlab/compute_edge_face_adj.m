function e2f = compute_edge_face_adj(F)
% compute_edge_face_adj - compute faces adjacent to each edge
%
%   e2f(i,j) and e2f(j,i) are the ids of the two faces adjacent to
%   edge (i,j). 

	nf = size(F, 2);
	F = double(F);
	i = [F(1,:) F(2,:) F(3,:)];
	j = [F(2,:) F(3,:) F(1,:)];
	s = [1:nf 1:nf 1:nf];
	e2f = sparse(i,j,s); 

	% % boundary edge - adgacent face idx -1
	% A = (e2f > 0) - ((e2f + e2f')>0);
	% e2f = e2f + A;

end