



L1=imread('naczynia1.jpg');
L1=(L1)<150;
figure; imshow(L1);
L2=bwmorph(L1,'skel',Inf);
figure; imshow(L2);
L3=bwmorph(L2,'spur',Inf);
figure; imshow(L3);
L4=bwmorph(L3,'clean',Inf);
figure; imshow(L4);



pause;
close all