L1=imread('portret1.jpg');
figure;
imshow(L1);
figure;
imhist(L1);
[y,x]=imhist(L1);
figure;
bar(x,y);
figure;
stairs(x,y);