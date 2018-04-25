
koniec = 0;
figure;
L1 = imread('portret.jpg');

imshow(L1);
[x,y,mouseclick] = ginput(1)
[x1,y1,mouseclick] = ginput(1)

a = y1 - y;
b = x1 - x;
L2 = L1(y:y1,x:x1)
L3 = imresize(L2, 2, 'linear');
L4 = imresize(L2, 2, 'cubic');

figure;
imshow(L3);
figure;
imshow(L4)


sleep(2)
close all;