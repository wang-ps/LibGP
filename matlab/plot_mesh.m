function h = plot_mesh(V, F, options)

% plot_mesh - plot a 3D mesh.
%
%   plot_mesh(vertex,face, options);
%
%   'options' is a structure that may contains:
%       - 'normalv' : a (nvertx x 3) array specifying the normals at each vertex.
%       - 'edge_color' : a float specifying the color of the edges.
%       - 'face_color' : a float specifying the color of the faces.
%       - 'face_vertex_color' : a color per vertex or face.


%% check input
if nargin<2, error('Not enough arguments.'); end

options.null = 0;
light = get_options(options, 'light', true);
face_vertex_color = get_options(options, 'face_vertex_color',  ones(size(V))'*0.5); 
edge_color = get_options(options, 'edge_color', 'none');
normal = get_options(options, 'normalv', []);

%% 3D mesh
V = V';
F = F';

if size(face_vertex_color,1) == size(V,1)
    shading_type = 'interp';
else
    shading_type = 'flat';
end

h = patch('vertices',V, 'faces',F, 'FaceVertexCData',face_vertex_color, ...
    'FaceColor', shading_type, 'EdgeColor', edge_color);

% plot the vertex normals
if ~isempty(normal)   
    n = size(V,1);
    if size(normal, 1) ~= n, normal = normal'; end
    
    normal_scaling  = get_options(options, 'normal_scaling', .8);
    subsample_normal = get_options(options, 'subsample_normal', min(4000/n,1) );
    sel = randperm(n); sel = sel(1:floor(end*subsample_normal));    
    
    hold on;
    quiver3(V(sel,1), V(sel,2), V(sel,3), ...
        normal(sel,1), normal(sel,1), normal(sel,1), normal_scaling);
    hold off;
end

%% camera options
cameratoolbar('show');
cameratoolbar('SetMode', 'orbit');
cameratoolbar('SetCoordSys','none');
 
lighting phong;
camproj('perspective');
axis square; axis off; axis tight; axis equal;

if light % || strcmp(shading_type, 'interp')
    % shading interp;
    camlight left;
    camlight right;
    camlight(0, 180); % back
    material([0.4 0.5 0.5])
end


