L=imread('xD.jpg');
L = rgb2gray(L);
figure(1);

L = imnoise(L, 'salt & pepper', 0.1);
imshow(L);

% filtr górnoprzepustowy HP2
Maska2 = [1,3,1; 3,16,3; 1,3,1];
L2=filter2(Maska2, L);
L2=mat2gray(L2);
figure(3); imshow(L2, 'InitialMagnification','fit');

pause;
close all