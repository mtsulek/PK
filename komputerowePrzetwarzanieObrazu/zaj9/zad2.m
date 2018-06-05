L=imread("portret.jpg");

figure(1); imshow(L, 'InitialMagnification');
Maska1 = ones(3);
L1=filter2(Maska1, L);
L1=mat2gray(L1);
figure(2); imshow(L1, 'InitialMagnification');
Maska2 = ones(5);
L2=filter2(Maska2, L);
L2=mat2gray(L2);
figure(3); imshow(L2, 'InitialMagnification');
Maska3 = ones(16);
L3=filter2(Maska3, L);
L3=mat2gray(L3);
figure(4); imshow(L3, 'InitialMagnification');


pause;

close all