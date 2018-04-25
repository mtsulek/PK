L1 = imread('portret.jpg');
figure;
imshow(L1);
[x,y,mouseclick] = ginput(1)
figure;
L2 = circshift (L1, [round(y) round(x)]);
imshow(L2);


%macierz xD
macierz = [1,3,4;7,8,9;5,2,6]
macierz;

circshift(macierz,[2,1])


