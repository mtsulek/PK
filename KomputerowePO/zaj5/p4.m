L1 = imread('portret.jpg');

while 0<1
  wyb = menu('Menu','Dodaj 0-1','Odejmij 0-1','Logarytmuj','Pierwiastek','Potęga','Przywróc oryginalny obraz','Wyjdz','dodaj kontrast');
  switch wyb
    case 1
      rand1 = rand(1);
      L1 = L1 + (rand1 * 10);
      imshow(L1);
    case 2
      rand1 = rand(1);
      L1 = L1 - (rand1 * 10);
      imshow(L1);
    case 3
      L1 = log(L1 + 1);
      imshow(L1);
    case 4
      L1 = sqrt(L1);
      imshow(L1);
    case 5
      L1 = power(L1, 1.5);
      imshow(L1);
    case 6
      L1 = imread('portret.jpg');
      imshow(L1);
    case 7
      close
      break;
    case 8
      #L1 = imadjust(L1,[120/255, 255/255],[0 1]);
      L1=imadjust(L1,[0.3 0.7],[],0.6)
      figure;
      imshow(L1);
  end
  figure;
  imhist(L1);
  [y,x]=imhist(L1);
end
close all;
