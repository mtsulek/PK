pkg load image;

L1 = imread('KPO.gif');
L1 = L1<128;
figure; imshow(L1);

SE = strel('disk',2, 0);
L2 = imclose(L1,SE);

figure; imshow(L2)
L2 = imopen(L2,SE);

figure; imshow(L2)
pause;
close all;