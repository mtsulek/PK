L1 = imread('portret.jpg');
figure; imshow(L1)
axis on
[m n]=size(L1);
sr = round(size(L1,2)/2);
L1_l = L1(:,1:sr);
L1_r = L1(:,sr+1:end);
L1_rs = imresize(L1_r,[m sr*4]);
L2 = [L1_l L1_rs];
figure;
imshow(L2);
axis on
L2 = imresize(L2, [m n]);
figure;
imshow(L2);
axis on