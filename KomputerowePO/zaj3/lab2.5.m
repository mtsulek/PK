L1=imread('./portret.jpg');
figure(1);
imshow(L1);
L2a=imrotate(L1,-60,'linear');
figure(2);
imshow(L2a);