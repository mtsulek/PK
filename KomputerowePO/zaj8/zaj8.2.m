L = imread('cells1.bmp');
imshow(zeros(600,800));
subplot(1,2,1),imshow(L);
subplot(1,2,2),imhist(L);
prompt = {'Podaj prog binaryzacji:'};
odp = inputdlg(prompt);


prog = str2num(odp{1});
[x,y] = ginput(1);
%tol = str2num(odp{2});
tol = L(fix(y), fix(x))


L2 = (L<(prog+tol))&(L>(prog-tol));






figure;
imshow(L2);

