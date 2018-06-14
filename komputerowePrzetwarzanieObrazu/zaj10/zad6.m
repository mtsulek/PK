L1=imread('rysunek.bmp');
figure; imshow(L1);
SE=[0 1 0;-1 1 1;-1 -1 0];
L2=bwhitmiss(L1,SE);
figure; imshow(L2);

SE=[0 1 0;-1 1 1;-1 -1 0];
L2=bwhitmiss(L1,SE);
figure; imshow(L2);

SE = imrotate([0 1 0;-1 1 1;-1 -1 0], 90);
L3=bwhitmiss(L1,SE);
figure; imshow(L3);


SE = imrotate([0 1 0;-1 1 1;-1 -1 0], 180);
L4=bwhitmiss(L1,SE);
figure; imshow(L4);


SE = imrotate([0 1 0;-1 1 1;-1 -1 0], 270);
L5=bwhitmiss(L1,SE);
figure; imshow(L5);

LxD = L2 + L3 + L4 + L5;
imshow(LxD);

sum(sum(LxD)) 

pause;
close all