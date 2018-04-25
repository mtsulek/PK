L1=imread('portret.jpg');
figure;
imshow(L1);
L2=(L1)+50;
figure;
imshow(L2)



L1=imread('portret.jpg');
L1=double(L1)/255;
figure;
imshow(L1);
L2=L1+0.3;
figure;
imshow(L2)