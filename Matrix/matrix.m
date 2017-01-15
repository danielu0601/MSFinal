for i = 26:26:676
%for i = [26 676]
    M1  = rand(i);
    M1i = inv(M1); %M1^-1
    M1t = transpose(M1); %M1'
    M2  = rand(i);
    M2i = inv(M2); %M1^-1
    M2t = transpose(M2); %M1'
    
    % transpose metrix
    [fid, message] = fopen(['./Matrix' int2str(i) 'trans.txt'],'w');
    for j = 1:i
        for k = 1:i
            fprintf(fid, '%f ', M1t(j,k) );
        end
    end
    fprintf(fid, '\n\n');
    for j = 1:i
        for k = 1:i
            fprintf(fid, '%f ', M2t(j,k) );
        end
    end
    fclose(fid);
    
    % invert metrix
    [fid, message] = fopen(['./Matrix' int2str(i) 'inv.txt'],'w');
    for j = 1:i
        for k = 1:i
            fprintf(fid, '%f ', M1i(j,k) );
        end
    end
    fprintf(fid, '\n\n');
    for j = 1:i
        for k = 1:i
            fprintf(fid, '%f ', M2i(j,k) );
        end
    end
    fclose(fid);
end
