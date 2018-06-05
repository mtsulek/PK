L1=imread('portret.jpg');
figure;
imshow (L1);
L2a=padarray(L1,[30 80],128,'post');
figure;
imshow (L2a);
L2b=padarray(L1,80,128,'both');
figure;
imshow (L2b);
L2c=padarray(L1,[80 20],'replicate','both');
figure;
imshow (L2c);
L2d=padarray(L1,30,'symmetric','pre');
figure;
imshow (L2d);
L2e=padarray(L1,[60 60],'symmetric','pre');
figure;
imshow (L2e)