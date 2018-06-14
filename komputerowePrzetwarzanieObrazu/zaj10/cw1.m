


L=imread('xD.jpg');
figure; imshow(L);
SE=ones([3, 3]);
E=imerode(L,SE);


figure; imshow(E);
L2=L-E; figure; 
imdilate(L2, SE);
imdilate(L2, SE);
imdilate(L2, SE);
imdilate(L2, SE);
imshow(L2); 
%?????????????
pause;
close all;