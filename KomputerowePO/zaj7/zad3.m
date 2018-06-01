L1=imread('portret.jpg');
figure
imshow(zeros(800,800));
[r c] = size(L1);
[x,y] = meshgrid(0:c-1,0:r-1);
z = double(L1);
surfc(x,y,z);
axis([0 c 0 r 0 255])
L2 = imresize(L1,size(L1)/8,'nearest');
figure
imshow(zeros(800,800));
[r c] = size(L2);
[x,y] = meshgrid(0:c-1,0:r-1);
z = double(L2);
surfc(x,y,z);
axis([0 c 0 r 0 25])
colormap(jet)