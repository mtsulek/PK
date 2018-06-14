pkg load image;



L1=imread('kwadrat.bmp');
%L1=(L1)<150;
%rgb2gray(L1);
figure; imshow(L1);


L2a=bwmorph(L1,'shrink',inf);
figure; imshow(L2a);
%L2b=bwmorph(L1,'shrink',10);
%figure; imshow(L2b);
%L2c=bwmorph(L1,'shrink',40);
%figure; imshow(L2c);


L2a=bwmorph(L1,'thin',inf);
figure; imshow(L2a);
%L2b=bwmorph(L1,'thin',10);
%figure; imshow(L2b);
%L2c=bwmorph(L1,'thin',40);
%figure; imshow(L2c);


L2a=bwmorph(L1,'thicken',inf);
figure; imshow(L2a);
%L2b=bwmorph(L1,'thicken',10);
%figure; imshow(L2b);
%L2c=bwmorph(L1,'thicken',40);
%figure; imshow(L2c);

pause;
close all