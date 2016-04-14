function [ avgEdge ] = compute_avg_edge_length( V, F )
%COMPUTE_AVG_EDGE_LENGHT compute the average edge length

n = size(F, 2);

v1 = V(:, F(1, :));
v2 = V(:, F(2, :));
v3 = V(:, F(3, :));

avgEdge = sum( sqrt( sum((v1-v2).^2, 1)) ) + ...
          sum( sqrt( sum((v1-v3).^2, 1)) ) + ...
          sum( sqrt( sum((v3-v2).^2, 1)) ) ;
      
avgEdge = avgEdge / (3*n);

end

