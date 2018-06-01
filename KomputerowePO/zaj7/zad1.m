[L1,map1]=imread('Victoire.tif');
L1=ind2rgb(L1,map1);
figure;
imshow(L1);
L1r=L1(:,:,1);
L1g=L1(:,:,2);
L1b=L1(:,:,3);
figure;
[x,y]=hist(L1r(:));

bar(y,x,1/255);
xlabel('Nasycenie koloru czerwonego','FontSize',13,'FontName','ArialCE');
ylabel('Ilość pikseli[/]','FontSize',13,'FontName','Arial CE');
L2r=histeq(L1r);
L2g=histeq(L1g);
L2b=histeq(L1b);
figure;
imshow(cat(3,L2r,L2g,L2b));
figure;
[x,y]=imhist(L2r(:));

bar(y,x,1/255);
xlabel('Nasycenie koloru czerwonego','FontSize',13,'FontName','ArialCE');
ylabel('Ilość pikseli[/]','FontSize',13,'FontName','Arial CE');