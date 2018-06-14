L=imread('bacteria.bmp');
figure; imshow(L);
SE=ones([3, 3]);
E=imerode(L,SE);
figure; imshow(E)
L2=L-E; figure; imshow(L2);