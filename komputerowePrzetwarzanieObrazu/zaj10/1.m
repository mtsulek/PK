se1=strel('pair',[3,-2]);
figure; imshow(getnhood(se1),'InitialMagnification','fit');

se2=strel('line',10,60);
figure; imshow(getnhood(se2),'InitialMagnification','fit');

se3=strel('disk',10, 0);
figure; imshow(getnhood(se3),'InitialMagnification','fit');

se4=strel('diamond',3);
figure; imshow(getnhood(se4),'InitialMagnification','fit');

se5=strel('periodicline',2,[-2,1]);
figure; imshow(getnhood(se5),'InitialMagnification','fit');

se6=strel('ball',15,3);
figure; imshow(getnhood(se4),'InitialMagnification','fit');
