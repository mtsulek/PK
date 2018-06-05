L1a=imread('wykr_10.tif');
figure;
imshow(L1a);
L1b=imread('wykr_14.tif');
figure;
imshow(L1b);
L2=L1a&L1b; %lub: L2=bitand(L1a,L1b)
figure; 
imshow(L2);



L2=L1a|L1b; %lub: L2=bitand(L1a,L1b)
figure; 
imshow(L2);


L2=xor(L1a, L1b); 
figure; 
imshow(L2);


L2=xor(L1a, L1b)&L1a; 
figure; 
imshow(L2);


pause;
close all