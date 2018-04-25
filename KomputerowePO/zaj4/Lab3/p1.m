L = zeros(4);
L(1:2:end,1:2:end) = 1;
L(2:2:end,2:2:end) = 1;
imshow(L,'InitialMagnification','fit');
L2a=imresize(L,[8 8],'nearest');
L2a=imrotate(L2a, 90, 'linear');

pause
figure
imshow(L2a, 'InitialMagnification','fit')
pause
L2b=imresize(L,[8 8],'bilinear')
L2b=imrotate(L2b, 90, 'bilinear');

figure
imshow(L2b, 'InitialMagnification','fit')
pause
L2c=imresize(L,[8 8],'bicubic')
L2c=imrotate(L2c, 90, 'bicubic');

figure
imshow(L2c, 'InitialMagnification','fit')
pause
L2d=imresize(L,[8 8],'lanczos3')
L2d=imrotate(L2d, 90, 'lanczos3');

figure
imshow(L2d, 'InitialMagnification','fit')