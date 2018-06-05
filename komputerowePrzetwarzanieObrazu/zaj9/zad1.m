L=ones([16, 16])*255;
L(6:11, 6:11)=(0:43:255)'*ones([1 6]);
L(14,14)=0;
L=uint8(L);
figure(1); imshow(L, 'InitialMagnification','fit');
K = ones(3);
L1=filter2(K, L, 'valid');
L2=filter2(K, L, 'same');
L3=filter2(K, L, 'full');
L1=mat2gray(L1);
figure(2); imshow(L1, 'InitialMagnification','fit');
L2=mat2gray(L2);
figure(3); imshow(L2, 'InitialMagnification','fit');
L3=mat2gray(L3);
figure(4); imshow(L3, 'InitialMagnification','fit');



pause;
close all