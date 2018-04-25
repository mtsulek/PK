% ZADANIE3
L = imread('kurak.jpg');
figure;
[y, x] = size(L);

% SZAROSC
L = rgb2gray(L);

% WYROWNANIE
L1 = imadjust(L,[0 1],[0 150/255]); %NIE DZIAŁA MI NA LINUXIE I NIE WIEM CZY DOBRZE, ALE CHYBA TAK
[y,x] = imhist(L);
imhist(L1);


y = (1:128)'/128;
z = (1:64)'/64;
x1 = ones(64,1);

r = [x1*0.7; 0.7*x1; y];
g = [z; 1-z; x1; 1-z];
b = [1-z; z; x1*0.3; x1*0.3];

mapa = [r g b];

% MAPA KOLOROW
figure;
rgbplot(mapa);


% KURAK W MAPIE KOLOROW
figure;
imshow(L,'Colormap',mapa);


