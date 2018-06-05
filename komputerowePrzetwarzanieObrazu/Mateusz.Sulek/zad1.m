% ZADANIE1
pkg load image

L = imread('portret.jpg');
figure;
[y, x] = size(L);

L1 = L(1:y/3,1:x);
L2 = L(125:2*y/3,1:x);
L3 = L(250:y,1:x);

% rotate
L31 = imrotate(L3, 180)

% resize
L1 = imresize(L1, [x-(y-x) y]);
L2 = imresize(L2, [x-(y-x) y]);
L2 = imresize(L3, [x-(y-x) y]);

imshow(L1);
figure;
imshow(L2);
figure;
imshow(L31);
figure;
y, x
