L1 = imread('kwiaty.jpg');
figure; imshow(L1);
L1 = double(L1)/255;


hold on

setbright = ['w = get(suwak,''Value''); L2 = L1; L2 = L2 + w; imshow(L2)'];
suwak = uicontrol('Style','Slider',...
'Position',[10 40 25 400],...
'Min',-1,'Max',1,'Value',0,...
'Callback',setbright);



red = L1(:,:,1); % Red channel
green = L1(:,:,2); % Green channel
blue = L1(:,:,3); % Blue channel



setbright = ['w = get(suwak2,''Value''); L2 = L1; L2(:,:,1) = L1(:,:,1+w); imshow(L2)'];
suwak2 = uicontrol('Style','Slider',...
'Position',[50 40 25 400],...
'Min',-1,'Max',1,'Value',0,...
'Callback',setbright);
