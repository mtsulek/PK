L1=imread('mikolaj.jpg');
figure;
imshow(L1);
level = graythresh(L1);
L2 = im2bw(L1,level);
figure;
imshow(L2);