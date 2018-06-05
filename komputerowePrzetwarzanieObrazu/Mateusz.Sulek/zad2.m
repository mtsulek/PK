% ZADANIE2
L = imread('portret.jpg');
figure;
imshow(L);

[y, x] = size(L);

wartoscPix = L(180, 150)

for i = 1:y
  for j = 1:x
  
    if (L(i,j) > wartoscPix)
      L(i,j) = L(i,j) + 20; 
    endif
    
    if (L(i,j) < wartoscPix)
      L(i,j) = L(i,j) - 70; 
    endif
    
    if (L(i,j) == wartoscPix)
      L(i,j) = L(i,j) = 255; 
    endif
    
  endfor
endfor

imshow(L);
