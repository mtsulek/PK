
L = imread("portret.jpg");
figure(1); imshow(L, 'InitialMagnification');
Maska1 = [1,4,1; 4,12,4; 1,4,1];
L1=filter2(Maska1, L);
L1=mat2gray(L1);
figure(2); imshow(L1, 'InitialMagnification');
Maska2 = [1,3,1; 3,16,3; 1,3,1];
L2=filter2(Maska2, L);
L2=mat2gray(L2);
figure(3); imshow(L2, 'InitialMagnification');

L9999999999 = imabsdiff(L1, L2);
figure(4); imshow(L9999999999, 'InitialMagnification');

pause;
close all