[L1a,map1a] = imread('Beaux.bmp');
L1a=ind2gray(L1a,map1a);
L1a=L1a(201:650,101:700);
[L1b,map1b] = imread('drzewo.bmp');
L1b=ind2gray(L1b,map1b);
figure
[w k] = size(L1a)
for i=1:k
L2a(:,i) = L1a(:,i);
imshow(L2a);
pause(0.01);
end