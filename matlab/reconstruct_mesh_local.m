function [ V1 ] = reconstruct_mesh_local( V, F, N1, it_num )

	if ~exist('it_num', 'var'), it_num = 10; end

	% pre-compute
	vfr = compute_vtx_face_ring(F);

	V1 = V;
	for it = 1 : it_num
		% face center
		Fc = compute_face_center(V1, F);

		% update vertex
		V2 = V1;
		parfor i = 1 : size(V1, 2)
			vt = zeros(3, 1);
			for fi = vfr{i}
				vt = vt +  N1(:, fi)' * (Fc(:, fi) - V2(:, i)) * N1(:, fi);
			end
			V1(:, i) = V1(:, i) + vt / length(vfr{i});
		end
	end
end
