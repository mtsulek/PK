
koniec = 0;
figure;
L1 = imread('portret.jpg');

while koniec ~= 1
  imshow(L1);
  [x,y,mouseclick] = ginput(1)
  [x1,y1,mouseclick] = ginput(1)
   if mouseclick == 3
    koniec = 1;
    close all;
    break;
   end
  a = y1 - y;
  b = x1 - x;

  L2 = circshift (L1, [round(a) round(b)]);
  L1 = L2;
  
end

close all;