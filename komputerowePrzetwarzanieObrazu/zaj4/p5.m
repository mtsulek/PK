L1 = imread('portret.jpg');
figure;
imshow(L1)
[r,c] = size(L1)
x = 0:r;
y = round(15*sin(x/5)+16);
L2 = L1;
for i=1:r
L2(i,:) = [L1(i,(c-y(i)):c), L1(i,1:(c-y(i)-1))];
end
figure; imshow(L2)