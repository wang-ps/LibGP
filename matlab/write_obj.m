function succ = write_obj(V, F, fileName)
% write vertex and face to *.obj file
	
    fid = fopen(fileName, 'w');
	succ = size(V, 1) == 3 && size(F, 1) == 3 && fid > 0;
	if succ
	    fprintf(fid, 'v %f %f %f\n', V);
	    fprintf(fid, 'f %d %d %d\n', F);    
	    fclose(fid);
	end
end
