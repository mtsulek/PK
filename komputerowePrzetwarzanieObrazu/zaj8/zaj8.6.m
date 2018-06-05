[L1a,map1a] = imread('Beaux.bmp');
L1a=ind2gray(L1a,map1a);
figure; imshow(L1a);
L1a=L1a(801:1250,101:700); %wycięcie odpowiedniego fragmentu obrazu
figure; imshow(L1a);
[L1b,map1b] = imread('drzewo.bmp');
L1b=ind2gray(L1b,map1b);
figure;imshow(L1b)
L2a=L1a+L1b;
figure; imshow(mat2gray(L2a))