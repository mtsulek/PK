%pkg load image trzeba wpisac
L1=imread('portret.jpg');
figure;
imshow(zeros(500,400));
subplot(3,2,[1 3 5]), subimage(L1);
axis off
title('Obraz wyjsciowy');
subplot(3,2,2), subimage(imrotate(L1,90));
axis off
title('Obrot o 90^o');
subplot(3,2,4), subimage(imrotate(L1,180));
axis off
title('Obrot o 180^o');
subplot(3,2,6), subimage(imrotate(L1,270));
axis off
title('Obrot o 270^o');