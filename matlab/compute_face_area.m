function [ areas ] = compute_face_area(V, F)

normalf = cross( V(:,F(2,:))-V(:,F(1,:)), V(:,F(3,:))-V(:,F(1,:)));
areas = 0.5 * sqrt( sum(normalf.^2) );

end

