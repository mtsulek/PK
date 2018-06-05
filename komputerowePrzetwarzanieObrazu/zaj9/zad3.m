L=ones([16, 16])*255;
L(6:11, 6:11)=(0:43:255)'*ones([1 6]);
L(14,14)=0;

L = imread("portret.jpg");


L=uint8(L);
figure(1); imshow(L, 'InitialMagnification','fit');
Maska1 = [1,1,1; 1,2,1; 1,1,1];
L1=filter2(Maska1, L);
L1=mat2gray(L1);
figure(2); imshow(L1, 'InitialMagnification','fit');
Maska2 = [1,1,1; 1,0,1; 1,1,1];
L2=filter2(Maska2, L);
L2=mat2gray(L2);
figure(3); imshow(L2, 'InitialMagnification','fit');



pause;
close all