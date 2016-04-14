function [ face_center ] = compute_face_center( V, F )

face_center = ( V(:, F(1, :)) + ...
				V(:, F(2, :)) + ...
    			V(:, F(3, :)) ) / 3;

end
