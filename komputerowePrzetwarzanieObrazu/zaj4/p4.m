L1 = imread('portret.jpg');
figure;
imshow(L1);
[r,c] = size(L1)
L2 = reshape(L1, r*2, c/2);
figure;
imshow(L2)
L3 = reshape(L1, r/2, c*2);
figure;
imshow(L3)